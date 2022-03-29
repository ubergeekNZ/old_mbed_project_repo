
import sys
from PyQt4 import QtCore, QtGui

# This is where we actually get the module creted by Qt
from qtHelloWorld import Ui_Form

class MyForm(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        # Make Signal/Slot connections
        # Connect the button to the function below
        QtCore.QObject.connect(self.ui.pushButton, 
                              QtCore.SIGNAL("clicked()"),
                                self.buttonclick)
    def buttonclick(self):
        self.ui.textBrowser.insertPlainText("Hello World!\n")


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myform = MyForm()
    myform.show()
    sys.exit(app.exec_())
 
    