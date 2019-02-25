<html>
<body>

<?php
    // connect to db
    $connect = mysqli_connect("127.0.0.1", "root", "", "Qgiv");
    // Check connection
    if ($connect->connect_error) {
        die("Connection failed: " . $connect->connect_error);
    }

$sql="INSERT INTO transactions (idtransactions, amount, status, payment_type, user_email, timestamp) VALUES (DEFAULT, '$_POST[amount]','$_POST[status]', '$_POST[payment_type]', '$_POST[user_email]', NOW())";

if (!mysqli_query($connect, $sql))
  {
  die("Connection failed: " . $connect->connect_error);
  }
mysqli_close($connect);
header('Location: transactions.php');
exit();
?>

</body>
</html>
