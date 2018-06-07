#include "urllineedit.h"
#include <QToolButton>
#include <QUrl>
#include <QPainter>
#include <QProgressBar>
#include <QMovie>
#include <QStyle>
#include <QThread>
#include <QStyleOptionFrame>

/*!
 * \brief UrlLineEdit::UrlLineEdit Кастомная реализация элемента QLineEdit
 * \param parent QWidget
 */
UrlLineEdit::UrlLineEdit(QWidget *parent)
: QLineEdit(parent),
//
m_favButton(new QToolButton(this)),
m_clearButton(new QToolButton(this)) {
    /*
     * Возможности:
     * 1. Отображение загрузки страницы при помощи progressbar
     * 2. Кнопка очищения адресной строки
     * 3. Если соединение защищено (SSL), устанавливается иконка замка
     */
    setFocusPolicy(this->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
    setSizePolicy(this->sizePolicy());
    setBackgroundRole(this->backgroundRole());
    setMouseTracking(true);
    setAcceptDrops(true);
    setAttribute(Qt::WA_MacShowFocusRect, true);
    QPalette p = this->palette();
    setPalette(p);

    // Устанавливаем иконку очищения адресной строки
    m_clearButton->setIcon(QIcon(QStringLiteral(":exitButton.png")));
    // По умолчанию (когда адресная строка пуста) она неактивна
    m_clearButton->setVisible(false);
    m_clearButton->setCursor(Qt::ArrowCursor);
    QString style(QStringLiteral("QToolButton { border: none; padding: 1px; }"));
    m_clearButton->setStyleSheet(style);
    m_favButton->setStyleSheet(style);
    setStyleSheet(QStringLiteral("QLineEdit{padding-left:%1px;padding-right:%2px;padding-top:5px;padding-bottom:5px;}")
            .arg(m_clearButton->sizeHint().width())
            .arg(m_favButton->sizeHint().width()));
    int minIconHeight = qMax(m_favButton->sizeHint().height(), m_clearButton->sizeHint().height());
    setMinimumSize(minimumSizeHint().width() +
            m_favButton->sizeHint().width() +
            m_clearButton->sizeHint().width(),
            qMax(minimumSizeHint().height(), minIconHeight));

    connect(m_clearButton, &QToolButton::clicked, this, &QLineEdit::clear);
    connect(this, &QLineEdit::textChanged, [this](const QString & text) {
        m_clearButton->setVisible(!text.isEmpty() && !isReadOnly());
    });
}

/*!
 * \brief UrlLineEdit::setWebView Устанавливает webView для того, чтобы впоследствие передавать прогресс для отрисовки progressbar
 * \param webView
 */
void UrlLineEdit::setWebView(QWebView *webView) {
    m_webView = webView;
    // Обновляем по мере прогресса
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(update()));
}

/*!
 * \brief UrlLineEdit::paintEvent Отрисовка элемента UrlLineEdit
 * \param e контекст отрисовки
 */
void UrlLineEdit::paintEvent(QPaintEvent *e) {
    // В начале - отрисовываем сам элемент QLineEdit
    QLineEdit::paintEvent(e);
    QPainter painter(this);
    QStyleOptionFrame panel;
    initStyleOption(&panel);
    QRect backgroundRect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);
    if (m_webView) {
        // Получаем прогресс загрузки страницы
        int progress = value;
        // Отрисовываем сам прогрессбар
        // Устанавливаем ему цвет
        QColor loadingColor = QColor(0x34,0x98,0xdb,0x66);
        painter.setBrush(loadingColor);
        // Границы делаем прозрачными
        painter.setPen(Qt::transparent);
        // Ширина - в зависимости от процесса загрузки
        int mid = (backgroundRect.width() + 50) / 100.0f * progress;
        //QRect progressRect(backgroundRect.x() - 25, backgroundRect.y() + backgroundRect.height(), mid, backgroundRect.height() / 2);
        QRect progressRect(backgroundRect.x() - 25, backgroundRect.y() - 5, mid, backgroundRect.height() + 10);
        painter.drawRect(progressRect);
    }
}

/*!
 * Подстраивает размер кнопок при изменении размера самого элемента
 * \brief UrlLineEdit::resizeEvent
 * \param event
 */
void UrlLineEdit::resizeEvent(QResizeEvent *event) {
    // Отрисовываем оригинальный QLineEdit
    QLineEdit::resizeEvent(event);
    // (для себя) sizeHint() - определяет рекомендованный размер для виджета
    QSize clearButtonSize = m_clearButton->sizeHint();
    // Перемещаем кнопку очищения адресной строки
    m_clearButton->move(rect().right() - clearButtonSize.width(), (rect().bottom() - clearButtonSize.height()) / 2);
    // Перемещаем favIcon
    m_favButton->move(rect().left(), (rect().bottom() - m_favButton->sizeHint().height()) / 2);
}

/**
 * @brief UrlLineEdit::setDeafultIcon Отображает иконку в зависимости от типа соединения (защищенного или нет)
 */
void UrlLineEdit::setDeafultIcon() {
    // Если соединение - защищенное
    if (m_webView && m_webView->url().scheme() == QLatin1String("https")) {
        setFavIcon(QIcon(QStringLiteral(":ssl.png")));
    } else {
        setFavIcon(QIcon(QStringLiteral(":notssl.png")));
    }
}

/**
 * @brief UrlLineEdit::url Возвращает URL
 * @return URL
 */
QUrl UrlLineEdit::url() const {
    return QUrl::fromUserInput(text());
}

/*!
 * Устанавливаем URL
 * \brief UrlLineEdit::setUrl
 * \param url
 */
void UrlLineEdit::setUrl(const QUrl &url) {
    setText(url.toString());
    setCursorPosition(0);
}

/*!
 * Устанавливаем favIcon
 * \brief UrlLineEdit::setFavIcon
 * \param icon
 */
void UrlLineEdit::setFavIcon(const QIcon &icon) {
    QPixmap pixmap = icon.pixmap(20, 20);
    m_favButton->setIcon(pixmap);
}

/*!
 * Устанавливаем прогресс для прогресс бара
 * \brief UrlLineEdit::setValue
 * \param setValue
 */
void UrlLineEdit::setValue(int setValue) {
    // Один из самых важных методов
    value = setValue;
    setValue = 0;
}
