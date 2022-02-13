import sqlite3

from PyQt5 import QtWidgets, QtCore, uic
from race_search import race_search
from race_places import race_places
from buyed_race_tickets import buyed_race_tickets
from buyed_race_tickets_with_class import buyed_race_tickets_with_class
from Reserve import Reserve


class Tickets_reservation_after_search(QtWidgets.QWidget):

    def __init__(self, widget, mas):
        super().__init__(widget, QtCore.Qt.Window)
        uic.loadUi("tickets_reservation_after_search.ui", self)
        self.setWindowTitle("Поиск рейсов")

        self.mas = mas
        self.table1 = race_search(mas['dateOut'], mas['pointOut'], mas['pointIn'])

        self.tableWidget.cellClicked.connect(self.selectRowTable1)
        self.tableWidget.cellClicked.connect(self.selectRowTable1)
        self.comboBox.currentTextChanged.connect(self.change_price_1)
        #self.label_6.setVisible(False)

        self.setTable1()

        if mas['toBack']:
            self.table2 = race_search(mas['dateIn'], mas['pointIn'], mas['pointOut'])
            self.tableWidget_2.cellClicked.connect(self.selectRowTable2)
            self.tableWidget_2.cellClicked.connect(self.selectRowTable2)
            self.comboBox_3.currentTextChanged.connect(self.change_price_2)
            self.setTable2()

        self.pushButton.clicked.connect(self.reserve)

        self.show()

    def setTable1(self):
        self.tableWidget.setRowCount(len(self.table1))
        self.tableWidget.setColumnCount(7)
        self.tableWidget.setHorizontalHeaderLabels(["Номер рейса","Дата вылета","Время вылета","Время прилета",
                                                    "Пункт вылета", "Пункт прилета", "Код рейса"])
        for i, value in enumerate(self.table1):
            self.tableWidget.setItem(i, 0, QtWidgets.QTableWidgetItem(str(value[0])))
            self.tableWidget.setItem(i, 1, QtWidgets.QTableWidgetItem(str(value[1])))
            self.tableWidget.setItem(i, 2, QtWidgets.QTableWidgetItem(str(value[2])))
            self.tableWidget.setItem(i, 3, QtWidgets.QTableWidgetItem(str(value[3])))
            self.tableWidget.setItem(i, 4, QtWidgets.QTableWidgetItem(str(value[4])))
            self.tableWidget.setItem(i, 5, QtWidgets.QTableWidgetItem(str(value[5])))
            self.tableWidget.setItem(i, 6, QtWidgets.QTableWidgetItem(str(value[6])))
        self.tableWidget.resizeColumnsToContents()


    def setTable2(self):
        self.tableWidget_2.setRowCount(len(self.table2))
        self.tableWidget_2.setColumnCount(7)
        self.tableWidget_2.setHorizontalHeaderLabels(["Номер рейса","Дата вылета","Время вылета","Время прилета",
                                                    "Пункт вылета", "Пункт прилета", "Код рейса"])
        for i, value in enumerate(self.table2):
            self.tableWidget_2.setItem(i, 0, QtWidgets.QTableWidgetItem(str(value[0])))
            self.tableWidget_2.setItem(i, 1, QtWidgets.QTableWidgetItem(str(value[1])))
            self.tableWidget_2.setItem(i, 2, QtWidgets.QTableWidgetItem(str(value[2])))
            self.tableWidget_2.setItem(i, 3, QtWidgets.QTableWidgetItem(str(value[3])))
            self.tableWidget_2.setItem(i, 4, QtWidgets.QTableWidgetItem(str(value[4])))
            self.tableWidget_2.setItem(i, 5, QtWidgets.QTableWidgetItem(str(value[5])))
            self.tableWidget_2.setItem(i, 6, QtWidgets.QTableWidgetItem(str(value[6])))
        self.tableWidget_2.resizeColumnsToContents()


    def selectRowTable1(self, row, column):
        self.raceOut1 = []
        for i in range(0, 7):
            self.raceOut1.append(self.tableWidget.item(row, i).text())
            self.tableWidget.item(row, i).setSelected(True)

        for i in self.table1:
            if str(i[0]) == str(self.raceOut1[0]):
                self.raceOut1.append(i[6])
                break


        buf = race_places(self.raceOut1[6])[0]
        self.priceOut1 = {
            "econom": buf[0],
            "econom_price": buf[3],
            "business": buf[1],
            "business_price": buf[4],
            "vip": buf[2],
            "vip_price": buf[5]
        }

        self.comboBox.clear()
        self.label_price1.setText("")
        if(self.priceOut1['econom'] != 0 and self.priceOut1['econom'] != None):
            self.comboBox.addItem("Эконом")
        if(self.priceOut1['business'] != 0 and self.priceOut1['business'] != None):
            self.comboBox.addItem("Бизнес")
        if(self.priceOut1['vip'] != 0 and self.priceOut1['vip'] != None):
            self.comboBox.addItem("VIP")


    def selectRowTable2(self, row, column):
        self.raceOut2 = []
        for i in range(0, 7):
            self.raceOut2.append(self.tableWidget_2.item(row, i).text())
            self.tableWidget_2.item(row, i).setSelected(True)

        for i in self.table2:
            if str(i[0]) == str(self.raceOut2[0]):
                self.raceOut2.append(i[6])
                break

        buf = race_places(self.raceOut2[6])[0]
        self.priceOut2 = {
            "econom": buf[0],
            "econom_price": buf[3],
            "business": buf[1],
            "business_price": buf[4],
            "vip": buf[2],
            "vip_price": buf[5]
        }

        self.comboBox_3.clear()
        self.label_price2.setText("")
        if (self.priceOut2['econom'] != 0 and self.priceOut2['econom'] != None):
            self.comboBox_3.addItem("Эконом")
        if (self.priceOut2['business'] != 0 and self.priceOut2['business'] != None):
            self.comboBox_3.addItem("Бизнес")
        if (self.priceOut2['vip'] != 0 and self.priceOut2['vip'] != None):
            self.comboBox_3.addItem("VIP")


    def change_price_1(self):
        self.comboBox_2.clear()

        if(self.comboBox.currentText() == "Эконом"):
            self.label_price1.setText(str(self.priceOut1['econom_price']))
            buf = buyed_race_tickets_with_class(self.raceOut1[0], self.raceOut1[1], "Эконом")
            self.buyed_race_places1 = []
            for i in range(0, len(buf)):
                self.buyed_race_places1.append(buf[i][7])

            for i in range(self.priceOut1['econom']):
                if len(self.buyed_race_places1) == 0:
                    self.comboBox_2.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places1)):
                        if i+1 == self.buyed_race_places1[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places1)-1:
                                self.comboBox_2.addItem(str(i+1))

        if(self.comboBox.currentText() == "Бизнес"):
            self.label_price1.setText(str(self.priceOut1['business_price']))
            buf = buyed_race_tickets_with_class(self.raceOut1[0], self.raceOut1[1], "Бизнес")
            self.buyed_race_places1 = []
            for i in range(0, len(buf)):
                self.buyed_race_places1.append(buf[i][7])

            for i in range(self.priceOut1['business']):
                if len(self.buyed_race_places1) == 0:
                    self.comboBox_2.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places1)):
                        if i+1 == self.buyed_race_places1[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places1) - 1:
                                self.comboBox_2.addItem(str(i+1))

        if(self.comboBox.currentText() == "VIP"):
            self.label_price1.setText(str(self.priceOut1['vip_price']))
            buf = buyed_race_tickets_with_class(self.raceOut1[0], self.raceOut1[1], "VIP")
            self.buyed_race_places1 = []
            for i in range(0, len(buf)):
                self.buyed_race_places1.append(buf[i][7])

            for i in range(self.priceOut1['vip']):
                if len(self.buyed_race_places1) == 0:
                    self.comboBox_2.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places1)):
                        if i+1 == self.buyed_race_places1[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places1) - 1:
                                self.comboBox_2.addItem(str(i+1))

    def change_price_2(self):
        self.comboBox_4.clear()

        if (self.comboBox_3.currentText() == "Эконом"):
            self.label_price2.setText(str(self.priceOut2['econom_price']))
            buf = buyed_race_tickets_with_class(self.raceOut2[0], self.raceOut2[1], "Эконом")
            self.buyed_race_places2 = []
            for i in range(0, len(buf)):
                self.buyed_race_places2.append(buf[i][7])

            for i in range(self.priceOut2['econom']):
                if len(self.buyed_race_places2) == 0:
                    self.comboBox_4.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places2)):
                        if i+1 == self.buyed_race_places2[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places2) - 1:
                                self.comboBox_4.addItem(str(i+1))

        if (self.comboBox_3.currentText() == "Бизнес"):
            self.label_price2.setText(str(self.priceOut2['business_price']))
            buf = buyed_race_tickets_with_class(self.raceOut2[0], self.raceOut2[1], "Бизнес")
            self.buyed_race_places2 = []
            for i in range(0, len(buf)):
                self.buyed_race_places2.append(buf[i][7])

            for i in range(self.priceOut2['business']):
                if len(self.buyed_race_places2) == 0:
                    self.comboBox_4.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places2)):
                        if i+1 == self.buyed_race_places2[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places2) - 1:
                                self.comboBox_4.addItem(str(i+1))

        if (self.comboBox_3.currentText() == "VIP"):
            self.label_price2.setText(str(self.priceOut2['vip_price']))
            buf = buyed_race_tickets_with_class(self.raceOut2[0], self.raceOut2[1], "VIP")
            self.buyed_race_places2 = []
            for i in range(0, len(buf)):
                self.buyed_race_places2.append(buf[i][7])

            for i in range(self.priceOut2['vip']):
                if len(self.buyed_race_places2) == 0:
                    self.comboBox_4.addItem(str(i+1))
                else:
                    for j in range(0, len(self.buyed_race_places2)):
                        if i+1 == self.buyed_race_places2[j]:
                            break
                        else:
                            if j == len(self.buyed_race_places2) - 1:
                                self.comboBox_4.addItem(str(i+1))

    def reserve(self):

        mas = {"surname": self.lineEdit_surname_2.text(),
               "name": self.lineEdit_name_2.text(),
               "lastName": self.lineEdit_last_name_2.text(),
               "passport": self.lineEdit_passport_2.text(),
               "id_race1": self.raceOut1[6],
               "race_number1": self.raceOut1[0],
               "place_class1": self.comboBox.currentText(),
               "place_price1":self.label_price1.text(),
               "place_number1": self.comboBox_2.currentText(),
               "toBack": self.mas['toBack'],
               }

        if mas['toBack']:
            mas['id_race2']=self.raceOut2[6]
            mas['race_number2']=self.raceOut2[0]
            mas['place_class2']=self.comboBox_3.currentText()
            mas['place_price2']=self.label_price2.text()
            mas['place_number2']=self.comboBox_4.currentText()

        if mas['surname'] == "" or mas['name'] == "" or mas['lastName'] == "" or mas['passport'] == ""\
            or mas['race_number1'] == "" or mas['id_race1'] == "" or mas['place_class1'] == "" \
            or mas['place_price1'] == "" or mas['place_number1'] == "":
            self.label_15.setVisible(True)
            self.label_15.setText("Заполните все поля")
            return
        if mas['toBack']:
            if (mas['race_number2'] == "" or mas['id_race2'] == ""
                              or mas['place_class2'] == "" or mas['place_price2'] == "" or mas['place_number2'] == ""):
                self.label_15.setVisible(True)
                self.label_15.setText("Выберите обратный рейс")
                return
        Reserve(self, mas)