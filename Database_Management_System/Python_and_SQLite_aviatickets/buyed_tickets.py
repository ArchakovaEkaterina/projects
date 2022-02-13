import sqlite3

def buyed_tickets(surname, name, last_name, passport, race_number1, race_number2):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT races.race_number, races.date_out, races.time_out, races.time_in, races.point_out, 
        races.point_in, tickets.place_class, tickets.place_number
        FROM races INNER JOIN (passengers INNER JOIN tickets ON passengers.id=tickets.id_passenger) 
        ON races.id=tickets.id_race
        WHERE passengers.surname="%s" AND passengers.name="%s" AND passengers.last_name="%s" AND
        passengers.passport_number="%s" AND (races.race_number="%s" OR races.race_number="%s")""" % (surname, name, last_name, passport, race_number1, race_number2)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result


