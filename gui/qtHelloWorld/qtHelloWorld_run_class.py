
import sys
from PyQt4 import QtCore, QtGui

# This is where we actually get the module creted by Qt
from qtHelloWorld import Ui_Form

class MyForm(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        # Instantiate the UI as defined by Qt Designer
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myform = MyForm()  # Instantiate the MyForm class above
    myform.show()      # Call the show method to make visible  
                       # This does not return until we close the window
    sys.exit(app.exec_())
 
    