Panduan Lengkap Perintah GitBerikut adalah kumpulan perintah Git yang paling sering digunakan, diurutkan berdasarkan alur kerja mulai dari konfigurasi awal hingga kolaborasi tim.⚙️ Konfigurasi Awal (Hanya sekali di setiap komputer)Perintah ini digunakan untuk mengatur identitas Anda.# Mengatur nama Anda yang akan muncul di setiap commit
git config --global user.name "Nama Lengkap Anda"

# Mengatur email Anda yang akan terhubung dengan setiap commit
git config --global user.email "emailanda@example.com"
🚀 Memulai RepositoriMembuat Repositori Baru (Lokal)Gunakan ini di dalam folder proyek yang belum menjadi repositori Git.git init
Mengambil Repositori dari Server (Clone)Gunakan ini untuk mengunduh proyek yang sudah ada dari URL (seperti GitHub).git clone <URL_repositori>
日常 Alur Kerja Dasar (Sehari-hari)Ini adalah siklus yang akan paling sering Anda lakukan untuk menyimpan pekerjaan Anda.1. Cek StatusLihat file mana yang sudah diubah, yang baru, atau yang sudah disiapkan untuk di-commit. Perintah ini juga akan menunjukkan di branch mana Anda sedang berada.git status
2. Menyiapkan Perubahan (Stage)Pilih perubahan mana yang ingin Anda simpan dalam commit berikutnya.# Menyiapkan satu file spesifik
git add <nama_file>

# Menyiapkan semua file yang berubah di folder saat ini dan subfolder
git add .
3. Menyimpan Perubahan (Commit)Simpan perubahan yang sudah disiapkan (staged) ke dalam riwayat (history) repositori lokal Anda.git commit -m "Tulis pesan commit yang deskriptif di sini"
🌳 Bekerja dengan Branch (Cabang)Branch memungkinkan Anda untuk bekerja pada fitur baru tanpa mengganggu kode utama.Melihat Semua BranchLihat daftar semua branch lokal. Branch yang aktif ditandai dengan *.git branch
Membuat Branch Barugit branch <nama_branch_baru>
Pindah ke Branch Laingit checkout <nama_branch_tujuan>
💡 Tips: Buat branch baru dan langsung pindah ke sana dalam satu perintah:git checkout -b <nama_branch_baru>
Menggabungkan Branch (Merge)Gabungkan perubahan dari branch lain ke branch Anda saat ini.Skenario: Menggabungkan branch wgg ke main.# 1. Pindah dulu ke branch target (yang akan menerima perubahan)
git checkout main

# 2. Jalankan perintah merge dari branch sumber
git merge wgg

# 3. (Penting) Unggah hasil merge ke GitHub agar semua orang mendapat versi terbaru
git push origin main
Menghapus Branch (Lokal)Hapus branch setelah selesai digabungkan.# Opsi -d (aman): hanya bisa menghapus jika branch sudah di-merge
git branch -d <nama_branch>

# Opsi -D (paksa): menghapus paksa meskipun belum di-merge
git branch -D <nama_branch>
🌐 Bekerja dengan Remote (Contoh: GitHub)Sinkronisasi antara repositori lokal Anda dengan server remote.Melihat Daftar RemoteCek koneksi remote yang sudah terdaftar. Biasanya bernama origin.git remote -v
Mengambil Perubahan dari Remote (Pull)Unduh riwayat terbaru dari remote DAN langsung coba gabungkan (merge) ke branch lokal Anda saat ini. Lakukan ini sebelum mulai bekerja untuk memastikan kode Anda paling update.git pull
Mengirim Perubahan ke Remote (Push)Unggah semua commit yang ada di branch lokal Anda ke branch di remote. Ini adalah langkah terakhir setelah git add dan git commit.# Format umum
git push <nama_remote> <nama_branch>

# Contoh paling sering digunakan
git push origin main
🔍 Inspeksi & MembandingkanMelihat Riwayat CommitLihat daftar semua commit yang telah dibuat.# Tampilan standar
git log

# Tampilan lebih ringkas, satu baris per commit
git log --oneline

# Tampilan dengan grafis percabangan
git log --graph --oneline --all
Melihat Perbedaan (Diff)Bandingkan perubahan pada file.# Membandingkan file di folder kerja dengan yang ada di staging area
git diff

# Membandingkan file di staging area dengan commit terakhir
git diff --staged
↩️ Membatalkan PerubahanMembatalkan Perubahan di Folder KerjaKembalikan file ke kondisi sama seperti commit terakhir. Hati-hati, perubahan yang belum di-commit akan hilang permanen.git checkout -- <nama_file>
Membatalkan git add (Unstage)Keluarkan file dari staging area, tetapi perubahannya tetap ada di folder kerja.git reset HEAD <nama_file>
Mengubah Commit TerakhirJika Anda lupa menambahkan file atau ada salah ketik di pesan commit terakhir.# Tambahkan file yang lupa
git add <file_yang_lupa>

# Jalankan amend, ini akan membuka editor untuk mengubah pesan commit
git commit --amend
