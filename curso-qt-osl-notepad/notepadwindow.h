#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit> // Qtextedit
#include <QFileDialog> // Elegir donde guardar el archivo.
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence> // accesos directos.
#include <QMessageBox>
#include <QToolBar>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT // Esta clase tiene sentencias de Qt.

public:
    NotepadWindow(QWidget *parent = 0); // No tiene padre
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        Salir_;
    QAction*        Deshacer_;
    QAction*        Rehacer_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarPegar_;
    QPlainTextEdit* txtEditor_;
    QClipboard *    portapapeles_;
    QMenu*          Ayuda_;
    QAction*        Ayudo_;
    QToolBar*       toolbar_;

};

#endif // NOTEPADWINDOW_H
