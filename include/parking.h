#pragma once

// Khởi tạo
void initParking();

// Cập nhật trạng thái 4 cảm biến
void updateParking();

// Có xe ở ô này không
bool isSlotOccupied(uint8_t slot);

// Có bao nhiêu xe
int getCarCount();

// Còn bao nhiêu chỗ
int getFreeSlot();

// Bãi đã đầy chưa
bool isParkingFull();

// Ô nào vừa có xe vào (-1 nếu không có)
int getEnteredSlot();

// Ô nào vừa có xe ra (-1 nếu không có)
int getExitedSlot();