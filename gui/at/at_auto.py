# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'at.ui'
#
# Created: Fri Jul 31 23:41:35 2015
#      by: PyQt4 UI code generator 4.10.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName(_fromUtf8("Form"))
        Form.resize(400, 300)
        self.command = QtGui.QLineEdit(Form)
        self.command.setGeometry(QtCore.QRect(110, 60, 113, 25))
        self.command.setObjectName(_fromUtf8("command"))
        self.schedule = QtGui.QPushButton(Form)
        self.schedule.setGeometry(QtCore.QRect(120, 180, 85, 26))
        self.schedule.setObjectName(_fromUtf8("schedule"))
        self.time = QtGui.QDateTimeEdit(Form)
        self.time.setGeometry(QtCore.QRect(90, 110, 194, 25))
        self.time.setObjectName(_fromUtf8("time"))

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(_translate("Form", "Form", None))
        self.schedule.setText(_translate("Form", "PushButton", None))

