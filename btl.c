#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Định nghĩa cấu trúc dữ liệu cho xe
typedef struct {
    char bienSo[20];
    int daDangKy;         // 0 = chưa đăng ký, 1 = đã đăng ký
    int daNapTien;        // 0 = chưa nạp tiền, 1 = đã nạp tiền
    time_t thoiGianVao;   // Thời gian xe vào
    long thoiGianNap;     // Thời gian đã nạp (tính bằng giây)
    long thoiGianConLai;  // Thời gian còn lại
} Xe;

// Khai báo biến toàn cục
#define MAX_XE 100
Xe danhSachXe[MAX_XE];
int soLuongXe = 0;

// Khai báo các hàm
void xeVao();
void xeRa();
int timXe(char *bienSo);
void luuDuLieu();
void docDuLieu();
void xuLyXeChuaDangKy(char* bienSo);
void xuLyXeDaDangKy(char* bienSo);

// Hàm main
int main() {
    int luaChon;
    
    // Đọc dữ liệu từ file (nếu có)
    docDuLieu();
    
    while (1) {
        printf("\n===== HE THONG QUAN LY NHA DE XE =====\n");
        printf("1. Xe vao\n");
        printf("2. Xe ra\n");
        printf("3. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        
        switch (luaChon) {
            case 1:
                xeVao();
                break;
            case 2:
                xeRa();
                break;
            case 3:
                printf("Dang thoat chuong trinh...\n");
                return 0;
            default:
                printf("Lua chon khong hop le! Vui long thu lai.\n");
                break;
        }
    }
    
    return 0;
}

// Xử lý khi xe vào
void xeVao() {
    char bienSo[20];
    int loaiXe;
    
    printf("\n===== XE VAO =====\n");
    printf("Nhap bien so xe: ");
    scanf("%s", bienSo);
    
    // Kiểm tra xe đã trong bãi chưa
    if (timXe(bienSo) != -1) {
        printf("Xe nay da o trong bai!\n");
        return;
    }
    
    printf("Chon loai xe:\n");
    printf("1. Xe chua dang ky\n");
    printf("2. Xe da dang ky\n");
    printf("Nhap lua chon: ");
    scanf("%d", &loaiXe);
    
    switch (loaiXe) {
        case 1:
            xuLyXeChuaDangKy(bienSo);
            break;
        case 2:
            xuLyXeDaDangKy(bienSo);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }
    
    luuDuLieu();
}

// Xử lý xe chưa đăng ký
void xuLyXeChuaDangKy(char* bienSo) {
    if (soLuongXe >= MAX_XE) {
        printf("Bai do xe da day!\n");
        return;
    }
    
    // Thêm xe vào hệ thống
    strcpy(danhSachXe[soLuongXe].bienSo, bienSo);
    danhSachXe[soLuongXe].daDangKy = 0;
    danhSachXe[soLuongXe].daNapTien = 0;
    danhSachXe[soLuongXe].thoiGianVao = time(NULL);
    danhSachXe[soLuongXe].thoiGianNap = 0;
    danhSachXe[soLuongXe].thoiGianConLai = 0;
    
    printf("Xe chua dang ky da vao bai. Thoi gian se duoc tinh khi xe ra.\n");
    soLuongXe++;
}

// Xử lý xe đã đăng ký
void xuLyXeDaDangKy(char* bienSo) {
    if (soLuongXe >= MAX_XE) {
        printf("Bai do xe da day!\n");
        return;
    }
    
    int chonNapTien;
    printf("Lua chon nap tien:\n");
    printf("1. Nap tien ngay\n");
    printf("2. Khong nap tien\n");
    printf("Nhap lua chon: ");
    scanf("%d", &chonNapTien);
    
    // Thêm xe vào hệ thống
    strcpy(danhSachXe[soLuongXe].bienSo, bienSo);
    danhSachXe[soLuongXe].daDangKy = 1;
    danhSachXe[soLuongXe].thoiGianVao = time(NULL);
    
    if (chonNapTien == 1) {
        long soTien;
        printf("Nhap so tien can nap (1 dong = 1 giay): ");
        scanf("%ld", &soTien);
        
        danhSachXe[soLuongXe].daNapTien = 1;
        danhSachXe[soLuongXe].thoiGianNap = soTien;
        danhSachXe[soLuongXe].thoiGianConLai = soTien;
        
        printf("Xe da dang ky vao bai voi %ld giay da nap.\n", soTien);
    } else {
        danhSachXe[soLuongXe].daNapTien = 0;
        danhSachXe[soLuongXe].thoiGianNap = 0;
        danhSachXe[soLuongXe].thoiGianConLai = 0;
        
        printf("Xe da dang ky vao bai khong nap tien. Thoi gian se duoc tinh khi xe ra.\n");
    }
    
    soLuongXe++;
}

// Xử lý khi xe ra
void xeRa() {
    char bienSo[20];
    
    printf("\n===== XE RA =====\n");
    printf("Nhap bien so xe: ");
    scanf("%s", bienSo);
    
    int viTri = timXe(bienSo);
    if (viTri == -1) {
        printf("Khong tim thay xe trong he thong!\n");
        return;
    }
    
    time_t thoiGianRa = time(NULL);
    long thoiGianGui = (long)difftime(thoiGianRa, danhSachXe[viTri].thoiGianVao);
    
    printf("\nThong tin xe:\n");
    printf("Bien so: %s\n", danhSachXe[viTri].bienSo);
    printf("Thoi gian da gui: %ld giay\n", thoiGianGui);
    
    if (danhSachXe[viTri].daDangKy) {
        if (danhSachXe[viTri].daNapTien) {
            // Tính toán thời gian còn lại
            long thoiGianConLaiCapNhat = danhSachXe[viTri].thoiGianConLai - thoiGianGui;
            
            if (thoiGianConLaiCapNhat >= 0) {
                printf("Thoi gian con lai: %ld giay\n", thoiGianConLaiCapNhat);
                printf("Khong can thanh toan them.\n");
            } else {
                printf("Vuot qua thoi gian da nap: %ld giay\n", -thoiGianConLaiCapNhat);
                printf("So tien can thanh toan them: %ld dong\n", -thoiGianConLaiCapNhat);
            }
        } else {
            // Đã đăng ký nhưng không nạp tiền
            printf("So tien can thanh toan: %ld dong\n", thoiGianGui);
        }
    } else {
        // Xe chưa đăng ký
        printf("So tien can thanh toan: %ld dong\n", thoiGianGui);
    }
    
    // Xóa xe khỏi hệ thống
    for (int i = viTri; i < soLuongXe - 1; i++) {
        danhSachXe[i] = danhSachXe[i + 1];
    }
    soLuongXe--;
    
    printf("Xe da ra khoi bai do.\n");
    luuDuLieu();
}

// Hàm tìm xe trong danh sách
int timXe(char* bienSo) {
    for (int i = 0; i < soLuongXe; i++) {
        if (strcmp(danhSachXe[i].bienSo, bienSo) == 0) {
            return i;
        }
    }
    return -1;
}

// Lưu dữ liệu ra file
void luuDuLieu() {
    FILE* file = fopen("database_xe.bin", "wb");
    if (file == NULL) {
        printf("Loi: Khong the luu du lieu!\n");
        return;
    }
    
    fwrite(&soLuongXe, sizeof(int), 1, file);
    fwrite(danhSachXe, sizeof(Xe), soLuongXe, file);
    
    fclose(file);
}

// Đọc dữ liệu từ file
void docDuLieu() {
    FILE* file = fopen("database_xe.bin", "rb");
    if (file == NULL) {
        printf("Khong tim thay du lieu cu. Bat dau voi database trong.\n");
        return;
    }
    
    fread(&soLuongXe, sizeof(int), 1, file);
    fread(danhSachXe, sizeof(Xe), soLuongXe, file);
    
    fclose(file);
}