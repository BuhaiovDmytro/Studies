import User from "./model.js";

export default class Controller {

    get_gender() {

        var radios = document.getElementsByName('radios');

        for (var i = 0, length = radios.length; i < length; i++) {
            if (radios[i].checked) {
                if (radios[i].id === "radio-male") {
                    return "Male";
                } else if (radios[i].id === "radio-female") {
                    return "Female";
                }
            }
        }
    }

    async set_user_cookie(email_){

        var result = await axios.get('/get_user', {
            params:
                {
                    email: email_,
                }
        });

        this.setCookie("name_", result.data['name'], 30);
        this.setCookie("email_", result.data['email'], 30);
        this.setCookie("sex", result.data['sex'], 30);
        this.setCookie("birthday", result.data['birthday'], 30);
    }

    getCookie(cname) {

        var name = cname + "=";
        var ca = document.cookie.split(';');
        for (var i = 0; i < ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0) === ' ') {
                c = c.substring(1);
            }
            if (c.indexOf(name) === 0) {
                return c.substring(name.length, c.length);
            }
        }
        return "Cookie error";
    }

    setCookie(cname, cvalue, exdays) {
        var d = new Date();
        d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
        var expires = "expires=" + d.toUTCString();
        document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
    }

    async signup() {

        let new_user = new User(document.getElementById('name_inp').value,
            document.getElementById('email_inp').value,
            this.get_gender(),
            document.getElementById('bd_inp').value,
            document.getElementById('pass_inp').value);

        axios.get('/add_user', {
            params:
                {
                    name: new_user.name,
                    email: new_user.email,
                    sex: new_user.sex,
                    birthday: new_user.birthday,
                    password: new_user.password
                }
        });
        window.open('poll.html', "_self");
    }

    async signin_onclick() {

        if(document.getElementById('email_field').value !== "") {


            var result = await axios.get('/validate_user', {
                params:
                    {
                        email: document.getElementById('email_field').value,
                        password: document.getElementById('password_field').value
                    }
            });

            if (result.data['valid'] === true) {
                this.set_user_cookie(document.getElementById('email_field').value);
                window.open('poll.html', "_self");
            } else {
                alert("Incorrect login or password");
            }
        }
        else{
            alert("Email field can't be empty");
        }
    }

    get_vote() {

        var radios = document.getElementsByName('radios');

        for (var i = 0, length = radios.length; i < length; i++) {
            if (radios[i].checked) {

                return radios[i].id ;
            }
        }

    }

    get_user(){
        let cur_user = new User();

        cur_user.name = this.getCookie("name_");
        cur_user.email = this.getCookie("email_");
        cur_user.sex = this.getCookie("sex");
        cur_user.birthday = this.getCookie("birthday");

        return cur_user;
    }
}