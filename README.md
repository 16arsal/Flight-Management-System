# C++ Flight Management System

A menu-driven C++ console program for practicing flight scheduling, graph traversal, reservations, passenger lookup, and basic sorting/searching operations.

The project is self-contained in one source file, `FlightManagementSystem.cpp`, and uses a small hardcoded flight network between Karachi, Lahore, and Islamabad.

## What This Project Demonstrates

- Struct-based modeling of flights, cities, and reservations
- Use of `std::vector` for flight lists and temporary result sets
- Sorting departures and arrivals by time
- Finding directly reachable cities
- Breadth-first search ideas for route/path traversal
- In-memory reservation storage
- Passenger schedule lookup and deletion
- Sorting passengers for a flight

## Current Flight Data

The program starts with six hardcoded flights:

| Flight No. | From | Departure | To | Arrival |
| ---: | --- | ---: | --- | ---: |
| 1 | Karachi | 830 | Islamabad | 950 |
| 2 | Karachi | 930 | Lahore | 1130 |
| 3 | Lahore | 1200 | Islamabad | 1400 |
| 4 | Islamabad | 1400 | Karachi | 1600 |
| 5 | Lahore | 1100 | Karachi | 1230 |
| 6 | Islamabad | 1500 | Lahore | 1630 |

The city list is also hardcoded:

- Karachi
- Lahore
- Islamabad

## Program Features

The main menu supports these actions:

1. Show all cities.
2. Show departures for a city.
3. Show arrivals for a city.
4. Show cities reachable from a city.
5. Show shortest path between two cities.
6. Find a route between two cities.
7. Make a reservation.
8. Print a passenger's reservation schedule.
9. Delete a passenger's reservation.
10. Print passengers for a flight.

## Code Structure

### Main structs

`FlightType` stores flight number, start city, departure time, end city, arrival time, and pointer fields intended for linked departure/arrival lists.

`CityListType` stores a city name and pointer fields intended for departure/arrival lists.

`ReservationType` stores reservation number, passenger name, start city, end city, flight number, departure time, and arrival time.

### Main functions

| Function | Purpose |
| --- | --- |
| `ShowAllCities()` | Prints the hardcoded city list. |
| `ShowDeparturesForCity(...)` | Filters flights by start city and sorts by departure time. |
| `ShowArrivalsForCity(...)` | Filters flights by end city and sorts by arrival time. |
| `ShowCitiesReachableFrom(...)` | Lists unique direct destinations from a city. |
| `FindShortestPath(...)` | Attempts breadth-first traversal over the flight network. |
| `ShowShortestPath(...)` | Prints the path returned by `FindShortestPath`. |
| `FindRoute(...)` | Placeholder; currently prints that the functionality is not implemented. |
| `MakeReservation(...)` | Adds an in-memory reservation for the first matching direct flight. |
| `PrintPassengerSchedule(...)` | Finds a reservation by passenger name. |
| `DeletePassengerReservation(...)` | Removes a matching passenger reservation from the in-memory array. |
| `PrintPassengersForFlight(...)` | Lists passengers associated with a flight number. |
| `GenerateCityOptions(...)` | Builds a sorted list of unique cities from the flight list; currently not used by the menu. |

## Build and Run

A C++17 compiler is enough. For example, with `g++`:

```bash
g++ -std=c++17 FlightManagementSystem.cpp -o flight_management
./flight_management
```

For stricter local checking:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic FlightManagementSystem.cpp -o flight_management
```

The program compiles under C++17. With warning flags enabled, the current code reports warnings for the placeholder `FindRoute` parameters and missing initializers for unused pointer fields in the hardcoded flight records.

## Example Interaction

```text
1. Show all cities
2. Show departures for a city
3. Show arrivals for a city
4. Show cities reachable from a city
5. Show shortest path between two cities
6. Find a route between two cities
7. Make a reservation
8. Print a passenger's reservation schedule
9. Delete a passenger's reservation
10. Print a list of passengers for a particular flight (in order of last name)
0. Exit
Enter your choice:
```

Example departure lookup:

```text
Enter the departure city: Karachi
List of flight departures for Karachi:
Flight No: 1, Departure Time: 830, Arrival City: Islamabad
Flight No: 2, Departure Time: 930, Arrival City: Lahore
```

## Known Limitations

- `FindRoute(...)` is not implemented yet and currently prints a placeholder message.
- Shortest-path reconstruction is unreliable for user-entered city strings because `FindShortestPath(...)` stores `const char*` keys in an `unordered_map`; pointer identity can differ even when city text matches.
- `MakeReservation(...)` does not currently reject routes with no matching direct flight, so reservation fields may be left uninitialized for invalid city pairs.
- Reservations are stored only in memory and disappear when the program exits.
- Flight and city data are hardcoded in `main()` rather than loaded from a file or database.
- `FlightType` and `CityListType` include linked-list pointer fields, but the current program primarily uses `std::vector` and does not build linked departure/arrival lists.
- Passenger sorting currently compares the full `passengerName` string, not strictly last name.
- There is no automated test suite.

## What I Learned

- How to model a small transportation network with structs.
- How to use vectors for filtering and sorting records.
- How graph traversal ideas such as BFS apply to route search.
- Why string handling choices matter in C++, especially when using raw `const char*` pointers as map keys.
- How menu-driven console programs can grow into clearer modules as features expand.

## Future Improvements

- Replace `const char*` city fields with `std::string`.
- Complete `FindRoute(...)` and fix shortest-path reconstruction.
- Validate reservations before storing them.
- Load flights and cities from external files.
- Store reservations persistently.
- Split the program into header/source files.
- Add tests for route search, reservation creation, deletion, and passenger lookup.
