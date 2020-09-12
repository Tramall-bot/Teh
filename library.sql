CREATE TABLE Position
(
  Pos_ID INT NOT NULL,
  Pos_Name INT NOT NULL,
  Pos_Salary INT NOT NULL,
  Pos_Duties INT NOT NULL,
  Pos_Requirements INT NOT NULL,
  PRIMARY KEY (Pos_ID)
);

CREATE TABLE Publisher
(
  Pub_ID INT NOT NULL,
  Pub_Name INT NOT NULL,
  Pub_City INT NOT NULL,
  Pub_Address INT NOT NULL,
  PRIMARY KEY (Pub_ID)
);

CREATE TABLE Genre
(
  Gen_ID INT NOT NULL,
  Gen_Name INT NOT NULL,
  Gen_Description INT NOT NULL,
  PRIMARY KEY (Gen_ID)
);

CREATE TABLE Book
(
  Bk_ID INT NOT NULL,
  Bk_Name INT NOT NULL,
  Bk_Author INT NOT NULL,
  Bk_Realise_Date INT NOT NULL,
  Pub_ID INT NOT NULL,
  Gen_ID INT NOT NULL,
  PRIMARY KEY (Bk_ID),
  FOREIGN KEY (Pub_ID) REFERENCES Publisher(Pub_ID),
  FOREIGN KEY (Gen_ID) REFERENCES Genre(Gen_ID)
);

CREATE TABLE Reader
(
  Rd_ID INT NOT NULL,
  Rd_Full_Name INT NOT NULL,
  Rd_BD_Date INT NOT NULL,
  Rd_Sex INT NOT NULL,
  Rd_Address INT NOT NULL,
  Rd_Phone_Number INT NOT NULL,
  Rd_Passport_Data INT NOT NULL,
  PRIMARY KEY (Rd_ID)
);

CREATE TABLE Employee
(
  Emp_ID INT NOT NULL,
  Emp_Full_Name INT NOT NULL,
  Emp_Age INT NOT NULL,
  Emp_Sex INT NOT NULL,
  Emp_Address INT NOT NULL,
  Emp_Phone_Number INT NOT NULL,
  Emp_Passport_Data INT NOT NULL,
  Pos_ID INT NOT NULL,
  PRIMARY KEY (Emp_ID),
  FOREIGN KEY (Pos_ID) REFERENCES Position(Pos_ID)
);

CREATE TABLE Returned_Books
(
  Rb_Return_Date INT NOT NULL,
  Rb_GiveOut_Date INT NOT NULL,
  Rb_Return_Flag INT NOT NULL,
  Emp_ID INT NOT NULL,
  Rd_ID INT NOT NULL,
  Bk_ID INT NOT NULL,
  FOREIGN KEY (Emp_ID) REFERENCES Employee(Emp_ID),
  FOREIGN KEY (Rd_ID) REFERENCES Reader(Rd_ID),
  FOREIGN KEY (Bk_ID) REFERENCES Book(Bk_ID)
);