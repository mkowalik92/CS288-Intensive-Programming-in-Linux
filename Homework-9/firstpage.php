<!DOCTYPE html>
<html>
	<head>
		<title>2017_11_30_10_12_30</title>
		<style>
			table, th, td {
				border: 1px solid black;
				border-collapse: collapse;
			}
			th, td {
				padding: 5px;
			}
			th {
				text-align: center;
			}
			td {
				text-align: left;
			}
		</style>
	</head>
	<body>
	<?php
		$servername = "localhost";
		$username = "cs288";
		$password = "1q1r0s3t";
		$dbname = "stocks";
		$conn = new mysqli($servername, $username, $password, $dbname);
		if($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
		}
		$table_name = "2017_11_30_10_12_30";
		$query = "SELECT * FROM $table_name ORDER BY num";
		$rows = $conn->query($query);
		//$nrows = $rows->num_rows;
		//echo "$ncol";
		echo "<h2>$table_name</h2>";
		echo "<table>";
		echo "<tr><th>#</th><th>Name</th><th>Symbol</th><th>Volume</th><th>Price</th><th>Change</th><th>% Change</th></tr>";		
		while($row = mysqli_fetch_array($rows)) {
			echo "<tr>";
			//$ncol = mysqli_num_fields($rows);
			for($col=0; $col<mysqli_num_fields($rows); $col++) {
				echo "<td>" . $row[$col] . "</td>";
			}
			echo "</tr>";
		}
		echo "</table>";
		$conn->close();
	?>
	</body>
</html>