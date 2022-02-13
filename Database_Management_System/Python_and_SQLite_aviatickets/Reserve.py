from PyQt5 import QtWidgets, QtCore, uic
import sqlite3
import datetime

from passengers_tickets import passengers_tickets
from buyed_tickets import buyed_tickets
from add_passenger import add_passenger
from add_ticket import add_ticket
from select_passenger import select_passenger

class Reserve(QtWidgets.QWidget):

    def __init__(self, widget, mas):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("check.ui", self)
        self.setWindowTitle("Чек")

        result = select_passenger(mas['surname'], mas['name'], mas['lastName'], mas['passport'])
        if len(result) == 0:
            add_passenger(mas['surname'], mas['name'], mas['lastName'], mas['passport'])

        self.table1 = [mas['surname'], mas['name'], mas['lastName'], mas['passport']]
        self.setTable1()

        result = select_passenger(mas['surname'], mas['name'], mas['lastName'], mas['passport'])
        add_ticket(result[0][0], mas['place_class1'], mas['place_number1'], mas['id_race1'])

        if mas['toBack']:
            add_ticket(result[0][0], mas['place_class2'], mas['place_number2'], mas['id_race2'])

        if mas['toBack']:
            race_number2 = mas['race_number2']
        else:
            race_number2 = ""
        self.table2 = buyed_tickets(mas['surname'], mas['name'], mas['lastName'], mas['passport'],
                                    mas['race_number1'], race_number2)
        self.setTable2()
        self.label_3.setVisible(True)

        if mas['toBack']:
            place_price2 = mas['place_price2']
        else:
            place_price2 = "0"
        self.label_3.setText(str(int(mas['place_price1']) + int(place_price2)))

        self.show()


    def setTable1(self):
        self.tableWidget.setRowCount(1)
        self.tableWidget.setColumnCount(4)
        self.tableWidget.setHorizontalHeaderLabels(["Фамилия", "Имя", "Отчество", "Номер паспорта",])
        self.tableWidget.setItem(0, 0, QtWidgets.QTableWidgetItem(self.table1[0]))
        self.tableWidget.setItem(0, 1, QtWidgets.QTableWidgetItem(self.table1[1]))
        self.tableWidget.setItem(0, 2, QtWidgets.QTableWidgetItem(self.table1[2]))
        self.tableWidget.setItem(0, 3, QtWidgets.QTableWidgetItem(self.table1[3]))
        self.tableWidget.resizeColumnsToContents()

    def setTable2(self):
        self.tableWidget_2.setRowCount(len(self.table2))
        self.tableWidget_2.setColumnCount(8)
        self.tableWidget_2.setHorizontalHeaderLabels(["Номер рейса", "Дата вылета", "Время вылета", "Время прилета",
                                                    "Пункт вылета", "Пункт прилета", "Класс места", "Номер места",
                                                    ])
        for i, value in enumerate(self.table2):
            self.tableWidget_2.setItem(i, 0, QtWidgets.QTableWidgetItem(str(value[0])))
            self.tableWidget_2.setItem(i, 1, QtWidgets.QTableWidgetItem(str(value[1])))
            self.tableWidget_2.setItem(i, 2, QtWidgets.QTableWidgetItem(str(value[2])))
            self.tableWidget_2.setItem(i, 3, QtWidgets.QTableWidgetItem(str(value[3])))
            self.tableWidget_2.setItem(i, 4, QtWidgets.QTableWidgetItem(str(value[4])))
            self.tableWidget_2.setItem(i, 5, QtWidgets.QTableWidgetItem(str(value[5])))
            self.tableWidget_2.setItem(i, 6, QtWidgets.QTableWidgetItem(str(value[6])))
            self.tableWidget_2.setItem(i, 7, QtWidgets.QTableWidgetItem(str(value[7])))
        self.tableWidget_2.resizeColumnsToContents()
