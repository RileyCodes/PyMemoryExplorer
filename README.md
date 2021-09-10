<br />
<p align="center">


  <h3 align="center">PyMemoryExplorer</h3>

  <p align="center">
    A lightning speed CPython object explorer via pure memory reading.
    <br />
    <a href="https://github.com/RileyCodes/PyMemoryExplorer/issues/new">Report Bug</a>
    ·
    <a href="https://github.com/RileyCodes/PyMemoryExplorer/issues/new">Request Feature</a>
  </p>
</p>


<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Features</a>
    </li>
  </ol>
</details>

 
## About The Project

PyMemoryExplorer can scan and parse objects contained in a CPython program.

The application of this library may vary. Often this is useful to fetch information from a 3rd party software that is using a Python interpreter.

It can also be used for high-performance debugging needs, where eval is too slow to do the job.


## Features

PyMemoryExplorer come with two features:

* Object Scanner - it scans a linked list in CPython named `_gc_head` to find all Python Object that is managed by garbage collector.
* Object Parser - it supports to read the memory of a object and parse it into C++ Objects for developer to use


## Usage

Please check `PyMemoryExplorerTest` which demonstrate basic usage of this library.

Please read known limitations before use.

Object scanning via  `_gc_head`

![image](https://user-images.githubusercontent.com/35380563/132791076-0802f9b2-5784-4cb2-9afd-19108050a520.png)

Parsed `PyDictObject`

![image](https://user-images.githubusercontent.com/35380563/132791230-dd080f9a-bda5-4f6d-a890-4e8c2c6c7731.png)


Parsed `PyListObject`(all the numbers are the memory address that points to the object in this list.)

![image](https://user-images.githubusercontent.com/35380563/132791355-33fb380e-68af-4e2a-8670-b3250cc42495.png)


Parsed `PyTupleObject`

![image](https://user-images.githubusercontent.com/35380563/132791398-f61272cd-3327-4842-9252-3ed43b4f7f90.png)


Walk through a `PyTupleObject` and parse str in it.

![image](https://user-images.githubusercontent.com/35380563/132791497-413752ce-d043-41f0-b1d9-59f0aef076c5.png)


All the basic data types is supported

![image](https://user-images.githubusercontent.com/35380563/132791832-fff88b43-a477-4dec-a521-c5b49e626952.png)


## Known Limitations

* this library is hardcoded for offical CPython 2.7.18 x64, however, only mininal effort should be needed to support that verions architecture and of CPython 
* The target Python program can be running and change the object while it's reading ,so object parsed can be partial or incorrect in some cases, to avoid this, simply pause the interpreter while reading memory.
* this library is hard coded to skip object contents too many stuff, such as a dict with 5000+ objects to ensure it's performance, you should read the source code and update them correspondingly


![image](https://user-images.githubusercontent.com/35380563/132792316-6524983c-3c1d-464b-8c42-73f2ff75b9ff.png)
