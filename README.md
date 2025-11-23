# CLI Image Processor

A high-performance command-line image editor written in C for manipulating NetPBM images (PPM/PGM).  
This project demonstrates **low-level memory management**, **binary file I/O**, and **mathematical algorithm implementation** for image processing.

---

## 📌 Project Overview

This application provides a robust interface for loading, editing, and saving images in both ASCII and Binary **NetPBM formats (P1–P6)**.

Unlike high-level libraries that abstract away the heavy lifting, this project implements image-processing algorithms **from scratch**, including:

- Kernel convolution for filters  
- Matrix transformations for rotation  

---

## 🚀 Key Features

### **Format Support**
- Full support for NetPBM formats **P1–P6**
- Works with **grayscale** and **RGB** images
- Handles both **ASCII** and **Binary** encodings

### **Memory Management**
- Dynamic allocation for images of arbitrary resolution
- Clean `malloc`/`free` strategies to avoid leaks

### **Image Filtering**
3×3 kernel convolution implementations for:
- Edge Detection  
- Sharpen  
- Box Blur  
- Gaussian Blur  

### **Geometric Transformations**
- Rotation (90°, 180°, 270°)  
- Cropping algorithms  

### **Analytical Tools**
- Histogram generation  
- Histogram Equalization for improved contrast  

---

## 🔧 Technical Highlights (For Recruiters)

This project showcases core fundamentals of **systems programming**:

### **Manual Memory Management**
- Extensive use of `malloc`, `calloc`, and `free`
- Complex operations (crop, reload, filter) handled without leaks

### **Binary Data Processing**
- Direct manipulation of file streams (`fread`, `fwrite`)
- Parsing NetPBM headers and pixel matrices manually

### **Modular Architecture**
- `image_editor.c` – command loop / CLI interface  
- `functii.c` – processing logic  
- `functii.h` – function prototypes & struct definitions  

### **Algorithm Implementations**
- **Filtering:** 3×3 convolution kernels with clamping  
- **Equalization:** full CDF-based histogram normalization  

---

## 🛠️ Installation & Compilation

### **Prerequisites**
- GCC compiler  
- Make  

### **Build Instructions**
```bash
git clone https://github.com/mihaicraciun1902/cli-image-processor.git
cd cli-image-processor
make
```

---

## 💻 Usage

Run the main executable:

```bash
./image_editor
```

---

## 📘 Command Examples

| Command | Description |
|--------|-------------|
| `LOAD <file>` | Load a NetPBM image into memory |
| `SELECT <x1> <y1> <x2> <y2>` | Select a pixel region |
| `SELECT ALL` | Select entire image |
| `ROTATE <angle>` | Rotate selection/image (±90, ±180, ±270) |
| `CROP` | Crop image to current selection |
| `APPLY <filter>` | Apply BLUR, SHARPEN, EDGE, GAUSSIAN_BLUR |
| `EQUALIZE` | Histogram equalization |
| `SAVE <filename> [ascii]` | Save result (optional ASCII format) |
| `EXIT` | Free memory and exit |

---

## 🖥️ Sample Session

```
> LOAD rsc/lenna.ppm
Loaded rsc/lenna.ppm

> SELECT 0 0 200 200
Selected 0 0 200 200

> APPLY BLUR
APPLY BLUR done

> SELECT ALL
Selected ALL

> ROTATE 90
Rotated 90

> SAVE output_lenna.ppm
Saved output_lenna.ppm
```

---

## 📂 Project Structure

```
├── image_editor.c   # Entry point and CLI command loop
├── functii.c        # Core logic (I/O, memory, math)
├── functii.h        # Structs & function prototypes
├── Makefile         # Build rules
└── README.md        # Documentation
```

---

## 👨‍💻 Author

**Mihai-Alexandru Crăciun**
* [LinkedIn](https://www.linkedin.com/in/craciunmihai1902/)
* [GitHub](https://github.com/mihaicraciun1902)
