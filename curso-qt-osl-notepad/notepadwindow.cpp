#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O)); // Especificar el acceso directo.
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

    Salir_ = new QAction(tr("&Salir"),this);
    Salir_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    mnuArchivo_ ->addAction(Salir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    Deshacer_ = new QAction(tr("&Deshacer"), this);
    Deshacer_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_ -> addAction(Deshacer_);

    Rehacer_ = new QAction(tr("&Rehacer"), this);
    Rehacer_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_ -> addAction(Rehacer_);

    Ayuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_ -> addMenu(Ayuda_);

    Ayudo_ = new QAction(tr("&Acerca"),this);
    Ayudo_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    Ayuda_ -> addAction(Ayudo_);

    actEditarCortar_ = new QAction(tr("&Cortar"),this);
    actEditarCortar_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_ -> addAction(actEditarCortar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Inicializamos el editor de texto
    txtEditor_ = new QPlainTextEdit(this);

    toolbar_ = new QToolBar;
    toolbar_ ->addAction(actEditarCortar_);
    toolbar_ ->addAction(actEditarCopiar_);
    toolbar_ ->addAction(actEditarPegar_);
    toolbar_ ->addAction(Salir_);
    addToolBar(toolbar_);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir())); // Conectar las acciones.
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(Salir_,             SIGNAL(triggered()), this,          SLOT(close()));
    connect(actEditarCortar_,   SIGNAL(triggered()), this,          SLOT(cut()));
    connect(Deshacer_,          SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(Rehacer_,           SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(Ayudo_,             SIGNAL(triggered()), txtEditor_,    SLOT(WindowAyuda()));


    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
    Deshacer_ -> deleteLater();
    actEditarCortar_ -> deleteLater();
}

void WindowAyuda(){
    QMessageBox help;
    QString mensaje = "Esta es la ayuda";
    help.setText(mensaje);
    help.exec();


}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "", // directorio en el que quieres que se abra.
                                                 tr("Archivos de texto plano (*.txt)")); // Especificar el tipo de fichero que se puede abrir.
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) { // booleano.
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        if(!nombreArchivo.endsWith(".txt"))
               nombreArchivo += ".txt";
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8()); // toUtf8 devuelve un Qstring representado en un Qbytearray.
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}
