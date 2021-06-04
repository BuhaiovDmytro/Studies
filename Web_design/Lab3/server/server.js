var express = require('express');
var path = require('path');
var app = express();
app.use(express.static('public'));



app.get('/css/profile_styles.css', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/css/profile_styles.css'));
})
app.get('/css/poll_styles.css', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/css/poll_styles.css'));
})
app.get('/css/styles.css', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/css/styles.css'));
})
app.get('/js/main.js', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/js/main.js'));
})
app.get('/js/view.js', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/js/view.js'));
})
app.get('/js/controller.js', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/js/controller.js'));
})
app.get('/js/model.js', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/js/model.js'));
})
app.get('/about.html', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/html', './about.html'));
})
app.get('/poll.html', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/html', './poll.html'));
})
app.get('/profile.html', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/html', './profile.html'));
})
app.get('/signin.html', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/html', './signin.html'));
})
app.get('/signup.html', (req, res) => {
    res.sendFile(path.join('/home/dmytro/KPI/Studies/Web_design/Lab3/client/html', './signup.html'));
})



app.get('/validate_user', function (req, res) {

    const sqlite3 = require('sqlite3').verbose();

    let db = new sqlite3.Database('/home/dmytro/KPI/Studies/Web_design/Lab3/server/db/poll.db');

    let sql = `SELECT password FROM users WHERE email = ?`;

    db.each(sql, [req.query.email], (err, row) => {

        if(`${row.password}` === req.query.password){

            res.send({'valid': true});
        }
        else{
            res.send({'valid': false});
        }
    });

    db.close();
});

app.get('/get_user', function (req, res) {

    const sqlite3 = require('sqlite3').verbose();

    let db = new sqlite3.Database('/home/dmytro/KPI/Studies/Web_design/Lab3/server/db/poll.db');

    let sql = `SELECT name, sex, birthday FROM users WHERE email = ?`;

    db.each(sql, [req.query.email], (err, row) => {

        res.send({'name' : `${row.name}`,
                        'email' : req.query.email,
                        'sex' : `${row.sex}`,
                        'birthday' : `${row.birthday}`});
    });

    db.close();
});

app.get('/add_user', function (req) {

    const sqlite3 = require('sqlite3').verbose();

    let db = new sqlite3.Database('/home/dmytro/KPI/Studies/Web_design/Lab3/server/db/poll.db');

    let new_user = [req.query.name, req.query.email, req.query.sex, req.query.birthday, req.query.password];

    let sql = `INSERT INTO users (name, email, sex, birthday, password) VALUES (?,?,?,?,?)`;

    db.run(sql, new_user, function(err) {
        if (err) {
            return console.error(err.message);
        }
    });

    db.close();
});

app.get('/get_polls', function (req, res) {

    const sqlite3 = require('sqlite3').verbose();

    let db = new sqlite3.Database('/home/dmytro/KPI/Studies/Web_design/Lab3/server/db/poll.db');

    let sql = `SELECT * FROM polls`;

    db.get(sql, (err, row) => {

        res.send({
            'poll_id': `${row.poll_id}`,
            'question': `${row.question}`,
            'ans1': `${row.ans1}`,
            'ans2': `${row.ans2}`
        });
    });

    db.close();
});

app.listen(3000);
