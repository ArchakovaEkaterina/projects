import sqlite3

from PyQt5 import QtWidgets, QtCore, uic
from race_search import race_search
from race_places import race_places

from buyed_race_tickets import buyed_race_tickets


class Buyed_race_tickets_after_input(QtWidgets.QWidget):

    def __init__(self, widget, mas):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("buyed_race_places.ui", self)
        self.setWindowTitle("Проданные билеты рейса")

        self.table1 = buyed_race_tickets(mas['race_number'], mas['dateOut'])
        self.setTable1()
        self.show()

    def setTable1(self):
        self.tableWidget.setRowCount(len(self.table1))
        self.tableWidget.setColumnCount(11)
        self.tableWidget.setHorizontalHeaderLabels(["Номер рейса", "Дата вылета", "Время вылета", "Время прилета",
                                                    "Пункт вылета", "Пункт прилета", "Класс места", "Номер места", "Фамилия", "Имя",
                                                    "Отчество", "Номер паспорта", ])
        for i, value in enumerate(self.table1):
            self.tableWidget.setItem(i, 0, QtWidgets.QTableWidgetItem(str(value[0])))
            self.tableWidget.setItem(i, 1, QtWidgets.QTableWidgetItem(str(value[1])))
            self.tableWidget.setItem(i, 2, QtWidgets.QTableWidgetItem(str(value[2])))
            self.tableWidget.setItem(i, 3, QtWidgets.QTableWidgetItem(str(value[3])))
            self.tableWidget.setItem(i, 4, QtWidgets.QTableWidgetItem(str(value[4])))
            self.tableWidget.setItem(i, 5, QtWidgets.QTableWidgetItem(str(value[5])))
            self.tableWidget.setItem(i, 6, QtWidgets.QTableWidgetItem(str(value[6])))
            self.tableWidget.setItem(i, 7, QtWidgets.QTableWidgetItem(str(value[7])))
            self.tableWidget.setItem(i, 8, QtWidgets.QTableWidgetItem(str(value[8])))
            self.tableWidget.setItem(i, 9, QtWidgets.QTableWidgetItem(str(value[9])))
            self.tableWidget.setItem(i, 10, QtWidgets.QTableWidgetItem(str(value[10])))
            self.tableWidget.setItem(i, 11, QtWidgets.QTableWidgetItem(str(value[11])))
        self.tableWidget.resizeColumnsToContents()