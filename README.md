# Hash-Function
Hashing adalah tindakan satu arah untuk mengubah data (disebut pesan) menjadi keluaran (disebut hash).
Fungsi hash adalah fungsi matematika yang mengubah data digital apa pun menjadi string keluaran dengan jumlah karakter yang tetap .

# Penjelasan Fungsi Hash:
  - Mid Square Hash: Menghitung hash dengan cara mengkuadratkan nilai integer dari kunci, kemudian mengambil digit tengah dari hasil kuadrat tersebut.
  - Folding: Teknik yang membagi string menjadi bagian-bagian dengan panjang tetap (biasanya 2 byte atau 4 byte), menjumlahkan bagian-bagian tersebut, dan kemudian mengambil 
             modulo dengan ukuran tabel hash.
  - Digit Extraction: Mengambil digit tengah dari nilai integer dari kunci.
  - Rotating Hash: Melakukan rotasi bit pada nilai integer dari kunci, kemudian mengambil modulo dengan ukuran tabel.

# Penjelasan Fungsi Collision Handling Method:
  - Linear Probing: Metode penanganan kolisi dengan mencari slot berikutnya yang kosong dalam tabel.
  - Rehashing: Metode alternatif untuk penanganan kolisi dengan melakukan hashing ulang dengan penambahan konstan.
  - Chaining: Metode di mana setiap bucket dalam hash table menyimpan linked list dari entri yang memiliki indeks hash yang sama. Ketika terjadi kolisi (dua atau lebih kunci 
              memiliki indeks hash yang sama), kunci tersebut ditambahkan ke akhir linked list di bucket tersebut.
