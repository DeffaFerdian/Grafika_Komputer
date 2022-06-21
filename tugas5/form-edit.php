<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style.css">
  <title>Edit Data | Sistem Informasi Mahasiswa</title>
  <script defer src="script.js"></script>
</head>
<body>
<?php 
$nim = $_GET['nim']; 

//koneksi database
include('koneksi.php');

//query
$query = "SELECT * FROM newtugas5 WHERE nim='$nim'";
$result = mysqli_query($conn, $query);

?>

  <h2 style="text-align:center; font-style:serif;">Sistem Informasi Mahasiswa</h2>
  <a href="index.php" style="margin-left:5%; padding:0.5% 1%;background-color:#0000FF;color:#fff;border-radius:2px;text-decoration:0;">Dashboard</a><br><br>
  <form role="form" action="editfinal.php" id="form" method="GET">
  <?php
		while ($row = mysqli_fetch_assoc($result)) {
		?>
    <table>
    <tr>
          <td><input type="hidden" name="nim" value="<?php echo $row['nim']; ?>"></td>
      </tr>

      <tr>
        <td>Nama Lengkap</td>
        <td>:</td>
          <td><Input type="text" name="namalengkap" value="<?php echo $row['nama_lengkap'] ?>" required></td>
      </tr>
      <tr>
        <td>Kota Asal</td>
        <td>:</td>
          <td><Input type="text" name="kotaasal" value="<?php echo $row['kota_asal'] ?>" required></td>
      </tr>
      <tr>
        <td>Tanggal Lahir</td>
        <td>:</td>
          <td><Input type="text" name="tanggallahir" value="<?php echo $row['tanggal_lahir'] ?>" required></td>
      </tr>
      <tr>
        <td>Nama Orang Tua</td>
        <td>:</td>
          <td><Input type="text" name="namaorangtua" value="<?php echo $row['nama_orangtua'] ?>" required></td>
      </tr>
      <tr>
        <td>Alamat Orang Tua</td>
        <td>:</td>
          <td><Input type="text" name="alamatorangtua" value="<?php echo $row['alamat_orangtua'] ?>" required></td>
      </tr>
      <tr>
        <td>Kode Pos</td>
        <td>:</td>
          <td><Input type="number" name="kodepos" value="<?php echo $row['kode_pos'] ?>" required></td>
      </tr>
      <tr>
        <td>Nomor Telepon</td>
        <td>:</td>
          <td><Input type="number" name="nomor_telepon" id="nomor_telepon"  value="<?php echo $row['nomor_telepon'] ?>" required></td>
      </tr>
      <tr>
        <td>status</td>
        <td>:</td>
          <td><select name="status">
            <option value="<?php echo $row['status'] ?>"><?php echo $row['status'] ?></option>
            <option value="">Pilih Status</option>
            <option value="TAMA">TAMA</option>
            <option value="WREDA">WREDA</option></select></td>
      </tr>
      <tr>
        <td></td>
        <td></td>
          <td><Input type="submit" name="Edit" value="simpan"></td>
      </tr>
    </table>
    <div id="error"></div>
  </form>

  <?php 
		}
		mysqli_close($conn);
		?>				
	</form>
  </body>
</html>   