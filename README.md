# MedStack
An object oriented C++ healthcare database management system using custom linked lists, inheritance, and dynamic memory management

A robust, object oriented C++ database management system designed to track, update, and manage facility patient records. 
Developed as the final project for Data Structures and Algorithms (ENGM 2283) at Dalhousie University

##Key Features
Dynamic Linked List Architecture: Implements a custom linked list composed of 'Record' nodes, ensuring O(1) time complexity
Granular Admissions Management: Utilizes inheritance to split patient tracking into 'Inpatient' and 'Outpatient' 
Strict Privacy & Unique ID Searching: Features an optimized query system restricted solely to Canadian Health Card Numbers to guarantee database lookup uniqueness (O(n) time complexity)
Rigorous Healthcare Management: Built with explicit destructor patterns and an atomic 'clear()' routine to safely deallocate local/global points

##OOP Design 
Base Class: 'Record' 
Derived Classes: 'Inpatient' and 'Outpatient'
Composition Components: 'Doctor' Class and 'Date' Class
