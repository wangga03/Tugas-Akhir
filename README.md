## Untuk push ke github :
1. $ git add .
2. $ git commit -m "<ini_pesan>"
3. $ git push

## Membuat branch baru (jika perlu)
$ git branch <nama_branch> : 
## pindah branch
$ git checkout <nama_baranch>

## Merge
### Misal kita ingin merge " wgg -> main " :
1. pergi ke main dulu : $ git checkout main
2. baru jalankan : $ git merge wgg
3. kemudian jalankan : $ git push

### Untuk cek sedang berada di branch mana :
$ git status
### kemudian akan muncul output :
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

berarti sedang berada di branch main


