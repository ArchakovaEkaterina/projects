from PyQt5 import QtWidgets, QtCore, uic
from Reserve_tickets import Reserve_tickets
from Search_passenger_tickets import Search_passenger_tickets
from Search_buyed_race_tickets import Search_buyed_race_tickets

class Menu_widget(QtWidgets.QWidget):

    def __init__(self):
        super().__init__()
        uic.loadUi("menu.ui", self)
        self.setWindowTitle("Продажа билетов")
        self.reserve_tickets_button.clicked.connect(self.reserve_tickets)
        self.search_passenger_tickets_button.clicked.connect(self.search_passenger_tickets)
        self.search_buyed_race_tickets_button.clicked.connect(self.search_buyed_race_tickets)
        self.show()

    def reserve_tickets(self):
        Reserve_tickets(self)

    def search_passenger_tickets(self):
        Search_passenger_tickets(self)

    def search_buyed_race_tickets(self):
        Search_buyed_race_tickets(self)