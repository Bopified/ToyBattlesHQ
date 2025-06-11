# 3.3 Setting up the database

Starting from version 2.0, I introduce MariaDB. This is much better since it allows you to have multiple regionals servers connect to the same, central database.


## How to Set Up the MariaDB Database
Before running the servers, you’ll need a MariaDB database properly configured with the right tables and data. Don’t worry — it’s not hard. Here's how to do it step by step:

### Step 1: Install MariaDB
If you haven’t already installed MariaDB:

- Go to https://mariadb.org/download/
- Download the version that matches your OS
- During installation, make sure to remember the root password (you’ll need it shortly)

### Step 2: Create the Database
Once MariaDB is installed:

- Open the MariaDB command line or a GUI like HeidiSQL, DBeaver, or MySQL Workbench.

- Log in using your root credentials.

- Run this command to create the database: `CREATE DATABASE `microvolts-db`;`

### Step 3: Import the Tables
You’ve been provided with a file called microvolts-db.md. This file contains the entire database structure and necessary insertions. You can find it in the root directory.

To import it:
#### Option A – Using Command Line
- `mysql -u root -p microvolts-db < path/to/microvolts-db.md`
(You’ll be prompted to enter your root password)

#### Option B – Using GUI (e.g., HeidiSQL)
- Open your database in the GUI
- Open the SQL file microvolts-db.md
- Run the whole script
This will create all tables and insert initial data (like items, shop content, etc.)

### Step 4: Set the Password via Environment Variable
For security, the server expects your database password to be stored in an environment variable (not directly in the config).

For example, if in `setup.ini` you wrote: `PasswordEnvironmentName = MICRO_DB_PW`


On Windows:
- Press Win + S → Search for “Environment Variables”
- Click “Edit the system environment variables”
- Add a new System Variable:
  - Name: MICRO_DB_PW
  - Value: your_db_password_here
Done!

### Step 5: Start mariaDB
Simply open a terminal and type `net start mariadb`. By default this will run on port 3306, so make sure to use the correct database port on the `config.ini` file!
