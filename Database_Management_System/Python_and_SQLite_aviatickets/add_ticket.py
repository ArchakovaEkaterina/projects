import sqlite3

def add_ticket(passenger_id, place_class, place_number, race_id):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """INSERT INTO tickets (id_passenger, id_race, place_class, place_number) VALUES (?, ?, ?, ?) """
        data = (passenger_id, race_id, place_class, place_number)
        cursor.execute(query, data)
        conn.commit()
        cursor.close()