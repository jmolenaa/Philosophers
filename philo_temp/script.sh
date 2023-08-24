func(){

echo
echo $1 $2 $3 $4 $5
sleep 2

./philo $1 $2 $3 $4 $5
}


make
func 5 301 100 100
func 4 300 100 100
func 150 300 100 100
func 3 150 50 50
func 3 149 50 50
func 3 151 50 50
func 2 100 50 50
func 2 99 50 50
func 2 101 50 50
func 199 149 50 50
func 199 150 50 50
func 199 151 50 50
func 199 152 50 50
func 199 153 50 50
func 199 154 50 50
func 199 155 50 50

