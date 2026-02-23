# 🌍 GlobeRank – Country Comparator System (C++)

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![STL](https://img.shields.io/badge/Library-STL-orange.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)
![DSA](https://img.shields.io/badge/Focus-Data%20Structures%20%26%20Algorithms-red.svg)

---

## 📌 Overview

**GlobeRank** is a modular C++ system designed to compare, rank, and analyze countries based on quantitative metrics such as population, GDP, or custom-defined parameters.

The project demonstrates real-world implementation of:

- Efficient data retrieval using hashing  
- Ranking using sorting algorithms  
- Modular Object-Oriented design  
- Performance-aware system development  

This is a DSA-driven system project structured for scalability and clarity.

---

## 🎯 Key Features

✔ Country comparison by metrics  
✔ Dynamic ranking system  
✔ Range-based filtering  
✔ Fast country lookup using hashing  
✔ Modular and extensible architecture  
✔ Menu-driven CLI interface  

---

## 🧠 Data Structures & Algorithms Used

| Concept | Implementation | Purpose |
|----------|---------------|----------|
| HashMap (`unordered_map`) | Constant-time lookup | O(1) country access |
| Sorting with Comparator | Ranking system | O(n log n) |
| Vector | Dynamic storage | Flexible data handling |
| File I/O | Persistence | Save & Load records |
| OOP | Class abstraction | Maintainability |

---

## 🏗 System Architecture

### High-Level Design

```
+-------------------+
|      main.cpp     |
|  (User Interface) |
+---------+---------+
          |
          v
+-------------------+
|   CountryStore    |
| (Data Management) |
+---------+---------+
          |
          v
+-------------------+
|     Comparator    |
|  (Ranking Logic)  |
+---------+---------+
          |
          v
+-------------------+
|      Country      |
|   (Data Model)    |
+-------------------+
```

---

## 📂 Project Structure

```
GlobeRank/
│
├── main.cpp                → Entry point (CLI Interface)
├── Country.h/.cpp          → Country data model
├── CountryStore.h/.cpp     → Data storage & management
├── Comparator.h/.cpp       → Ranking & comparison logic
├── Utils.h                 → Helper utilities
├── .gitignore
└── README.md
```

---

## ⚙️ Core Functionalities

- 🔍 Compare two countries by selected metric  
- 📊 Display top N ranked countries  
- 🎚 Filter countries within metric range  
- ➕ Add new country dynamically  
- 📁 Persist data using file handling (if enabled)  

---

## ⏱ Time Complexity Analysis

| Operation | Complexity |
|------------|------------|
| Add Country | O(1) |
| Lookup Country | O(1) |
| Rank Countries | O(n log n) |
| Filter by Range | O(n) |

Designed for efficiency and scalability.

---

## ▶ How to Compile & Run

### Windows (PowerShell)

```bash
g++ *.cpp -o GlobeRank.exe
./GlobeRank.exe
```

### Linux / macOS

```bash
g++ *.cpp -o GlobeRank
./GlobeRank
```

---

## 📈 Example Use Case

1. User selects ranking option  
2. System retrieves country data using HashMap  
3. Comparator applies sorting logic  
4. Ranked results displayed  

---

## 🚀 Future Enhancements

- 🌐 Real-time API integration  
- 🖥 GUI version (Qt / Web Frontend)  
- 🗄 Database integration (SQLite / MySQL)  
- 📊 Data visualization module  
- 🤖 Weighted multi-metric scoring system  

---

## 🎓 Learning Outcomes

This project demonstrates:

- Practical application of hashing for O(1) access  
- Implementation of efficient ranking algorithms  
- Structured modular C++ system design  
- Complexity-driven development thinking  
- Clean repository and version control management  

---

## 👨‍💻 Author

**Ankit Kumar**  
Aspiring Software Engineer | DSA Enthusiast  

---

## 📜 License

This project is licensed under the MIT License.

---

# ⭐ Why GlobeRank?

GlobeRank showcases how core DSA concepts can be transformed into a structured, real-world system project rather than isolated algorithm problems.

It reflects strong fundamentals in:
- Data Structures
- Algorithm Optimization
- Software Design
- Modular Architecture

---

If you found this project useful, consider giving it a ⭐.
