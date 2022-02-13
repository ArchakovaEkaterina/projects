import sqlite3

def race_places(id_race):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT races.econom_count, races.business_count, races.vip_count,
        races.econom_price, races.business_price, races.vip_price
        FROM races
        WHERE races.id="%s" """ % (id_race)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result