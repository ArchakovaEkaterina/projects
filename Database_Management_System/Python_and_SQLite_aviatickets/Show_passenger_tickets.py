from PyQt5 import QtWidgets, QtCore, uic
import sqlite3
import datetime

from passengers_tickets import passengers_tickets


class Show_passenger_tickets(QtWidgets.QWidget):

    def __init__(self, widget, mas):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("passanger_tickets.ui", self)
        self.setWindowTitle("Билеты пассажира")

        self.table1 = passengers_tickets(mas['surname'], mas['name'], mas['lastName'], mas['passport'])
        self.setTable1()
        self.show()

    def setTable1(self):
        self.tableWidget.setRowCount(len(self.table1))
        self.tableWidget.setColumnCount(11)
        self.tableWidget.setHorizontalHeaderLabels(["Номер рейса", "Дата вылета", "Время вылета", "Время прилета",
                                                    "Пункт вылета", "Пункт прилета", "Класс места",
                                                    "Фамилия", "Имя", "Отчество", "Номер паспорта",])
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
        self.tableWidget.resizeColumnsToContents()
