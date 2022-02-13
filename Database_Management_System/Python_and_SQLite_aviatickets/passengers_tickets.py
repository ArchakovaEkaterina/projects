import sqlite3

def passengers_tickets(surname, name, last_name, passport):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT races.race_number, races.date_out, races.time_out, races.time_in, races.point_out, 
        races.point_in, tickets.place_class, passengers.surname, passengers.name, passengers.last_name,
        passengers.passport_number 
        FROM races INNER JOIN (passengers INNER JOIN tickets ON passengers.id=tickets.id_passenger) 
        ON races.id=tickets.id_race
        WHERE passengers.surname="%s" AND passengers.name="%s" AND passengers.last_name="%s" AND
        passengers.passport_number="%s" ORDER BY races.date_out""" % (surname, name, last_name, passport)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result

