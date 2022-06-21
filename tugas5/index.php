<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Dashboard | Sistem Informasi Mahasiswa</title>
</head>

<body>
  <h2 style="text-align:center; font-style:serif;">Sistem Informasi Mahasiswa</h2>
  <a href="form-input.php" style="padding:0.5% 1%;background-color:#0000FF;color:#fff;border-radius:2px;text-decoration:0;">Tambahkan Data</a><br><br>
  <table border="1" cellspacings="5" width="100%">
    <tr style="text-align:center;font:weight:bold;background-color:white;">
      <td>No</td>
      <td>NIM</td>
      <td>Nama Lengkap</td>
      <td>Kota Asal</td>
      <td>Tanggal Lahir</td>
      <td>Nama Orang Tua</td>
      <td>Alamat Orang Tua</td>
      <td>Kode Pos</td>
      <td>Nomor Telepon</td>
      <td>Status</td>
      <td>Pilihan</td>
    </tr>

    <?php
    include 'koneksi.php';
    $no = 1;
    $select = mysqli_query($conn, "SELECT * FROM newtugas5");
    if (mysqli_num_rows($select) > 0) {
      while ($hasil = mysqli_fetch_array($select)) {
    ?>
        <tr style="text-align:center;">
          <td><?php echo $no++ ?></td>
          <td><?php echo $hasil['nim'] ?></td>
          <td><?php echo $hasil['nama_lengkap'] ?></td>
          <td><?php echo $hasil['kota_asal'] ?></td>
          <td><?php echo $hasil['tanggal_lahir'] ?></td>
          <td><?php echo $hasil['nama_orangtua'] ?></td>
          <td><?php echo $hasil['alamat_orangtua'] ?></td>
          <td><?php echo $hasil['kode_pos'] ?></td>
          <td><?php echo $hasil['nomor_telepon'] ?></td>
          <td><?php echo $hasil['status'] ?></td>
          <td>
            <a href="form-edit.php?nim=<?php echo $hasil['nim'] ?>">Edit</a> |
            <a href="delete.php?nim=<?php echo $hasil['nim'] ?>">Hapus</a>
          </td>
        </tr>
      <?php }
    } else { ?>
      <tr>
        <td colspan="11" align="center">Data Kosong</td>
      </tr>
    <?php } ?>
  </table>

</body>

</html>