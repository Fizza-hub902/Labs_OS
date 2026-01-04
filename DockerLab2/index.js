import express from express

const app = express()

//function handler(request,response){
    //response.send("Hello World!")
}
//app.get('/',handler)

app.use(express.static('public'))

app.listen(3000)