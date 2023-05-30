-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports;

SELECT * FROM crime_scene_reports WHERE day == 28 AND month == 7 AND year == 2020 AND street LIKE "Chamberlin%";

SELECT * FROM interviews WHERE day == 28 AND month == 7 AND year == 2020;

SELECT * FROM courthouse_security_logs WHERE day == 28 AND month == 7 AND year == 2020 AND hour LIKE 10 AND activity == "exit";

SELECT * FROM atm_transactions WHERE day == 28 AND month == 7 AND year == 2020 AND atm_location LIKE "Fifer%";

SELECT * FROM phone_calls WHERE day == 28 AND month == 7 AND year == 2020 AND duration <= 60;

SELECT * FROM flights WHERE day == 29 AND month == 7 AND year == 2020;

SELECT id FROM airports WHERE full_name LIKE "Fiftyville%";

SELECT * FROM airports JOIN flights ON airports.id = destination_airport_id WHERE day == 29 AND month == 7 AND year == 2020 AND hour == 8;

SELECT people.name FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number WHERE day == 28 AND month = 7 AND year = 2020 AND duration <= 60;

SELECT people.name FROM people JOIN phone_calls ON phone_calls.receiver = people.phone_number WHERE day == 28 AND month = 7 AND year = 2020 AND duration <= 60;

SELECT people.name, people.license_plate FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day == 28 AND month == 7 AND year == 2020 AND hour LIKE 10 AND courthouse_security_logs.activity == "exit";

SELECT people.name FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE flights.origin_airport_id == 8 AND flights.destination_airport_id == 4 AND day == 29 AND month == 7 AND year == 2020;

SELECT people.name, passengers.seat FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE flights.origin_airport_id == 8 AND flights.destination_airport_id == 4 AND day == 29 AND month == 7 AND year == 2020;

SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = (SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER By hour, minute LIMIT 1) INTERSECT SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" INTERSECT SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" INTERSECT SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit";

SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");