CREATE TABLE Employee
(
  Emp_ID INT NOT NULL,
  Emp_Full_Name VARCHAR NOT NULL,
  Emp_Age INT NOT NULL,
  Emp_Sex CHAR NOT NULL,
  Emp_Address  NOT NULL,
  Emp_Phone_Number INT NOT NULL,
  Emp_Passport_Data INT NOT NULL,
  PRIMARY KEY (Emp_ID)
);

CREATE TABLE Position
(
  Pos_ID INT NOT NULL,
  Pos_Name VARCHAR NOT NULL,
  Pos_Salary INT NOT NULL,
  Pos_Duties VARCHAR NOT NULL,
  Pos_Requirements VARCHAR NOT NULL,
  PRIMARY KEY (Pos_ID)
);

CREATE TABLE Publisher
(
  Pub_ID INT NOT NULL,
  Pub_Name VARCHAR NOT NULL,
  Pub_City VARCHAR NOT NULL,
  Pub_Address  NOT NULL,
  PRIMARY KEY (Pub_ID)
);

CREATE TABLE Genre
(
  Gen_ID INT NOT NULL,
  Gen_Name VARCHAR NOT NULL,
  Gen_Description VARCHAR NOT NULL,
  PRIMARY KEY (Gen_ID)
);

CREATE TABLE Book
(
  Bk_ID INT NOT NULL,
  Bk_Name VARCHAR NOT NULL,
  Bk_Author VARCHAR NOT NULL,
  Pub_ID INT NOT NULL,
  Bk_Realise_Date DATE NOT NULL,
  PRIMARY KEY (Bk_ID)
);

CREATE TABLE Reader
(
  Rd_ID INT NOT NULL,
  Rd_Full_Name VARCHAR NOT NULL,
  Rd_BD_Date DATE NOT NULL,
  Rd_Sex CHAR NOT NULL,
  Rd_Address  NOT NULL,
  Rd_Phone_Number INT NOT NULL,
  Rd_Passport_Data INT NOT NULL,
  PRIMARY KEY (Rd_ID)
);

CREATE TABLE Returned_Books
(
  Rb_Return_Date DATE NOT NULL,
  Rb_ID INT NOT NULL,
  Rb_GiveOut_Date DATE NOT NULL,
  Rb_Return_Flag INT NOT NULL,
  PRIMARY KEY (Rb_ID)
);