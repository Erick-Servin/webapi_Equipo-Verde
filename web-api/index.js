const express = require('express');
const app = express();
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

const Interruptor = require('./db/interruptor.js');

mongoose.connect('mongodb://localhost:27017/practica', function (err) {
	if (err) throw err;
});
console.log('conexion exitosa');


app.set('port', process.env.PORT || 3000);


app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.listen(app.get('port'), () =>{
	console.log(`Server on port ${app.get('port')}`);
});

app.post('/api', (req,res) => {
	console.log(req.body);
	//res.json({"hola":"mundo"});

	let inter = new Interruptor();

	inter.pos_izq = req.body.pos_izq;
	inter.pos_der = req.body.pos_der;
	inter.pos_cen = req.body.pos_cen;

	inter.save((err, inter1) =>{
		if(err) throw err;

		res.send({inter: inter1});
	})

});

