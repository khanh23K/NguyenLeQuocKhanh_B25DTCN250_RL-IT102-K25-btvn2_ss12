#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

struct NhanVien {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
};

void hienThiMenu(void);
int timKiemTheoMa(struct NhanVien ds[], int soLuong, int maNV);
void hienThiDanhSach(struct NhanVien ds[], int soLuong);
int themNhanVien(struct NhanVien ds[], int soLuong);
void suaNhanVien(struct NhanVien ds[], int soLuong);
int xoaNhanVien(struct NhanVien ds[], int soLuong);

void xoaBoDem(void);
int nhapSoNguyen(const char thongBao[], int *giaTri);
int nhapSoThuc(const char thongBao[], float *giaTri);
int nhapHoTen(char hoTen[], int kichThuoc);

void xoaBoDem(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int nhapSoNguyen(const char thongBao[], int *giaTri) {
    printf("%s", thongBao);

    if (scanf("%d", giaTri) != 1) {
        printf("=> Loi: Vui long nhap so nguyen hop le!\n");
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}

int nhapSoThuc(const char thongBao[], float *giaTri) {
    printf("%s", thongBao);

    if (scanf("%f", giaTri) != 1) {
        printf("=> Loi: Vui long nhap mot so hop le!\n");
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}
int nhapHoTen(char hoTen[], int kichThuoc) {
    printf("Ho ten: ");

    if (fgets(hoTen, kichThuoc, stdin) == NULL) {
        printf("=> Loi: Khong doc duoc ho ten!\n");
        return 0;
    }

    if (strchr(hoTen, '\n') == NULL) {
        int c = getchar();

        if (c != '\n' && c != EOF) {
            xoaBoDem();
            printf("=> Loi: Ho ten qua dai!\n");
            return 0;
        }
    }

    hoTen[strcspn(hoTen, "\n")] = '\0';

    if (strlen(hoTen) == 0) {
        printf("=> Loi: Ho ten khong duoc de trong!\n");
        return 0;
    }

    return 1;
}

void hienThiMenu(void) {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
}

int timKiemTheoMa(struct NhanVien ds[], int soLuong, int maNV) {
    int i;

    for (i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }

    return -1;
}

void hienThiDanhSach(struct NhanVien ds[], int soLuong) {
    int i;
    float tienPhat;
    float tienOT;
    float luongThucNhan;

    if (soLuong == 0) {
        printf("\n=> Danh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");

    for (i = 0; i < soLuong; i++) {
        tienPhat = (ds[i].phutMuon > 15) ? 50000.0f : 0.0f;

        tienOT = ds[i].soGioOT
                 * (ds[i].luongCoBan / 160.0f) * 1.5f;

        luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("\nMa NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f VND\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.2f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f VND\n", tienPhat);
        printf("Tien OT: %.0f VND\n", tienOT);
        printf("Luong thuc nhan: %.0f VND\n", luongThucNhan);
    }

    printf("\nTong so nhan vien: %d\n", soLuong);
}

int themNhanVien(struct NhanVien ds[], int soLuong) {
    struct NhanVien nv;
    int viTri;

    if (soLuong >= MAX_NHAN_VIEN) {
        printf("=> Loi: Danh sach da day!\n");
        return soLuong;
    }

    printf("\n--- THEM NHAN VIEN ---\n");

    if (!nhapSoNguyen("Ma NV: ", &nv.maNV)) {
        return soLuong;
    }

    if (nv.maNV <= 0) {
        printf("=> Loi: Ma nhan vien phai la so nguyen duong!\n");
        return soLuong;
    }

    viTri = timKiemTheoMa(ds, soLuong, nv.maNV);

    if (viTri != -1) {
        printf("=> Loi: Ma nhan vien da ton tai!\n");
        return soLuong;
    }

    if (!nhapHoTen(nv.hoTen, sizeof(nv.hoTen))) {
        return soLuong;
    }

    if (!nhapSoThuc("Luong co ban: ", &nv.luongCoBan)) {
        return soLuong;
    }

    if (nv.luongCoBan < 0) {
        printf("=> Loi: Luong co ban khong duoc am!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Phut di muon: ", &nv.phutMuon)) {
        return soLuong;
    }

    if (nv.phutMuon < 0) {
        printf("=> Loi: Phut di muon khong duoc am!\n");
        return soLuong;
    }

    if (!nhapSoThuc("So gio OT: ", &nv.soGioOT)) {
        return soLuong;
    }

    if (nv.soGioOT < 0) {
        printf("=> Loi: So gio OT khong duoc am!\n");
        return soLuong;
    }

    ds[soLuong] = nv;
    soLuong++;

    printf("=> Them nhan vien thanh cong!\n");

    return soLuong;
}

void suaNhanVien(struct NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    float luongMoi;
    int phutMuonMoi;
    float gioOTMoi;

    if (soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- CAP NHAT THONG TIN NHAN VIEN ---\n");

    if (!nhapSoNguyen("Nhap ma NV can sua: ", &maNV)) {
        return;
    }

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
        return;
    }

    printf("Nhan vien: %s\n", ds[viTri].hoTen);
    printf("Nhap thong tin moi:\n");

    if (!nhapSoThuc("Luong co ban moi: ", &luongMoi)) {
        return;
    }

    if (luongMoi < 0) {
        printf("=> Loi: Luong co ban khong duoc am!\n");
        return;
    }

    if (!nhapSoNguyen("So phut di muon moi: ", &phutMuonMoi)) {
        return;
    }

    if (phutMuonMoi < 0) {
        printf("=> Loi: Phut di muon khong duoc am!\n");
        return;
    }

    if (!nhapSoThuc("So gio OT moi: ", &gioOTMoi)) {
        return;
    }

    if (gioOTMoi < 0) {
        printf("=> Loi: So gio OT khong duoc am!\n");
        return;
    }

    ds[viTri].luongCoBan = luongMoi;
    ds[viTri].phutMuon = phutMuonMoi;
    ds[viTri].soGioOT = gioOTMoi;

    printf("=> Cap nhat thong tin thanh cong!\n");
}

int xoaNhanVien(struct NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    int i;

    if (soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return soLuong;
    }

    printf("\n--- XOA NHAN VIEN ---\n");

    if (!nhapSoNguyen("Ma NV can xoa: ", &maNV)) {
        return soLuong;
    }

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
        return soLuong;
    }

    for (i = viTri; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    soLuong--;

    printf("=> Xoa nhan vien thanh cong!\n");

    return soLuong;
}

int main(void) {
    struct NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon = -1;

    do {
        hienThiMenu();

        if (!nhapSoNguyen("Nhap lua chon: ", &luaChon)) {
            luaChon = -1;
            continue;
        }

        switch (luaChon) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;

            case 2:
                soLuong = themNhanVien(ds, soLuong);
                break;

            case 3:
                suaNhanVien(ds, soLuong);
                break;

            case 4:
                soLuong = xoaNhanVien(ds, soLuong);
                break;

            case 0:
                printf("Da thoat chuong trinh!\n");
                break;

            default:
                printf("=> Lua chon khong hop le!\n");
        }

    } while (luaChon != 0);

    return 0;
}

