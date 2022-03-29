
import sys
from PyQt4 import QtCore, QtGui

# This is where we actually get the module creted by Qt
from qtHelloWorld import Ui_Form
 
if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    Form = QtGui.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
    