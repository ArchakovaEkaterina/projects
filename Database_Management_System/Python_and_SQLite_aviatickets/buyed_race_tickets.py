import sqlite3

def buyed_race_tickets(race_number, date_out):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT races.race_number, races.date_out, races.time_out, races.time_in, races.point_out, 
        races.point_in, tickets.place_class, tickets.place_number, passengers.surname, passengers.name, passengers.last_name,
        passengers.passport_number
        FROM races INNER JOIN (passengers INNER JOIN tickets ON passengers.id=tickets.id_passenger) 
        ON races.id=tickets.id_race
        WHERE races.race_number="%s" AND races.date_out="%s" """ % (race_number, date_out)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result