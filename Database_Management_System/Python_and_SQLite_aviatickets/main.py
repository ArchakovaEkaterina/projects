from Menu_widget import Menu_widget
from PyQt5 import QtWidgets, QtCore, uic
import sys

# Press the green button in the gutter to run the script.

if __name__ == '__main__':
    app = QtWidgets.QApplication([])
    application = Menu_widget()
    sys.exit(app.exec())


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
