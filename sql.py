import sqlite3


class obertka:
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.conn = sqlite3.connect("base.db")

    def crateTable(self):
        c = self.conn.cursor()
        c.execute('CREATE TABLE if not exists stocks (date text, trans text, symbol text, qty real, price real)')
        self.conn.commit()



    def InsertValues(self, values):
        c = self.conn.cursor()
        c.executemany(f"INSERT INTO stocks VALUES (?,?,?,?,?)", values)
        self.conn.commit()

    def getTable(self, name):
        c = self.conn.cursor()
        c.execute('SELECT * FROM stocks ')
        print(c.fetchall())


if __name__ == '__main__':
    a = obertka()
    a.crateTable()
    a.InsertValues([('2006-03-28', 'BUY', 'IBM', 1000, 45.00)])
    a.getTable("123")
