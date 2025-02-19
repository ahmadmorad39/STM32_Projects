# DMA Memory-to-Memory Transfer Example
**Project Overview**
This project demonstrates the use of Direct Memory Access (DMA) for efficient memory-to-memory transfers on an STM32F4 microcontroller. The goal is to compare different memory copying methods and evaluate their performance in terms of execution time.

**Methods Compared**
The project measures the time taken by three different methods to transfer data between memory locations:
1. Simple memcpy32 Using a for Loop (92.417 µs)
   ```c
   for (uint32_t idx = 0; idx < size; idx++) {
    dst[idx] = src[idx];
    }
   This method iterates through each element and copies it using a simple assignment operation.
   ![Image](https://github.com/user-attachments/assets/c796f7a1-2495-4bce-b689-5af393f45699)
 2. Pointer Increment Copy (75.667 µs)
    ```c
    uint32_t arrayLength = size;
    while (arrayLength > 0) {
        *dst++ = *src++;
        arrayLength--;
    }
    This method uses pointer arithmetic to copy data, leading to better performance compared to the for loop approach.
    ![Image](https://github.com/user-attachments/assets/d59b3c88-b989-4c3e-8b7d-f011a4813ee2)
 3. DMA-Based Copy (11.792 µs)
    Using DMA, the memory transfer is handled by dedicated hardware, significantly reducing CPU load and improving efficiency.
    ![Image](https://github.com/user-attachments/assets/4210410c-6e2e-474b-b267-9db38389e897)
