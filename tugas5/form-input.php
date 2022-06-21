<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <script defer src="script.js"></script>
  <title>Tambahkan Data | Sistem Informasi Mahasiswa</title>
</head>

<body>
  <h2 style="text-align:center; font-style:serif;">Sistem Informasi Mahasiswa</h2><br>
  <a href="index.php" style="margin-left:5%; padding:0.5% 1%;background-color:#0000FF;color:#fff;border-radius:2px;text-decoration:0;">Dashboard</a><br><br>
  <form action="" id="form" method="POST" style="padding-left:5%;">
    <table>
      <tr>
        <td>NIM</td>
        <td>:</td>
          <td><Input type="number" name="nim" placeholder="nim" required></td>
      </tr>
      <tr>
        <td>Nama Lengkap</td>
        <td>:</td>
          <td><Input type="text" name="nama_lengkap" placeholder="nama_lengkap" required></td>
      </tr>
      <tr>
        <td>Kota Asal</td>
        <td>:</td>
          <td><Input type="text" name="kota_asal" placeholder="kota_asal" required></td>
      </tr>
      <tr>
        <td>Tanggal Lahir</td>
        <td>:</td>
          <td><Input type="text" name="tanggal_lahir" placeholder="tanggal_lahir" required></td>
      </tr>
      <tr>
        <td>Nama Orang Tua</td>
        <td>:</td>
          <td><Input type="text" name="nama_orangtua" placeholder="nama_orangtua" required></td>
      </tr>
      <tr>
        <td>Alamat Orang Tua</td>
        <td>:</td>
          <td><Input type="text" name="alamat_orangtua" placeholder="alamat_orangtua" required></td>
      </tr>
      <tr>
        <td>Kode Pos</td>
        <td>:</td>
          <td><Input type="number" name="kode_pos" placeholder="kode_pos" required></td>
      </tr>
      <tr>
        <td>Nomor Telepon</td>
        <td>:</td>
          <td><Input type="number" name="nomor_telepon" id="nomor_telepon" placeholder="nomor_telepon" required></td>
      </tr>
      <tr>
        <td>Status</td>
        <td>:</td>
          <td><select name="status">
            <option value="">Pilih Status</option>
            <option value="TAMA">TAMA</option>
            <option value="WREDA">WREDA</option></select></td>
      </tr>
      <tr>
        <td></td>
        <td></td>
          <td><Input type="submit" name="simpan" value="Simpan"></td>
      </tr>
    </table>
    <div id="error"></div>
  </form>
  </div>

  <?php
  include 'koneksi.php';
  if(isset($_POST['simpan'])){
    $insert = mysqli_query($conn, "INSERT INTO newtugas5 VALUES 
    ('".$_POST['nim']."', 
    '".$_POST['nama_lengkap']."',
    '".$_POST['kota_asal']."',
    '".$_POST['tanggal_lahir']."',
    '".$_POST['nama_orangtua']."',
    '".$_POST['alamat_orangtua']."',
    '".$_POST['kode_pos']."',
    '".$_POST['nomor_telepon']."',
    '".$_POST['status']."')");

    if($insert){
      echo 'berhasil disimpan';
    }else{
      echo 'gagal disimpan';
    }
  }
  ?>
</body>
</html>