<?php
    include('koneksi.php');
    $nim = $_GET['nim'];
    $nama_lengkap = $_GET['namalengkap'];
    $kota_asal = $_GET['kotaasal'];
    $tanggal_lahir = $_GET['tanggallahir'];
    $nama_orangtua = $_GET['namaorangtua'];
    $alamat_orangtua = $_GET['alamatorangtua'];
    $kode_pos = $_GET['kodepos'];
    $nomor_telepon = $_GET['nomor_telepon'];
    $status = $_GET['status'];

//query update
$query = "UPDATE newtugas5 SET nama_lengkap='$nama_lengkap' , kota_asal='$kota_asal' , tanggal_lahir='$tanggal_lahir' , nama_orangtua='$nama_orangtua' , kode_pos='$kode_pos' , nomor_telepon='$nomor_telepon' , status= '$status' WHERE nim='$nim' ";

if (mysqli_query($conn, $query)) {
	?>
		<script language="JavaScript">
			alert('Data Mahasiswa Berhasil Di Update!');
			document.location='index.php';
		</script>
	<?php
  }
  else{
    echo "ERROR, tidak berhasil". mysqli_error($conn);
  }
  
  mysqli_close($conn);
  ?>