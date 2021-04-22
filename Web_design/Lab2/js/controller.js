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

    signup() {

        let new_user = new User(document.getElementById('name_inp').value,
            document.getElementById('email_inp').value,
            this.get_gender(),
            document.getElementById('bd_inp').value,
            document.getElementById('pass_inp').value);

        this.setCookie("name_", '', 30);
        this.setCookie("email_", '', 30);
        this.setCookie("sex", '', 30);
        this.setCookie("birthday", '', 30);
        this.setCookie("password", '', 30);

        this.setCookie("name_", new_user.name, 30);
        this.setCookie("email_", new_user.email, 30);
        this.setCookie("sex", new_user.sex, 30);
        this.setCookie("birthday", new_user.birthday, 30);
        this.setCookie("password", new_user.password, 30);

        window.open('poll.html', "_self");
    }

    signin_onclick() {

        if (this.getCookie("email_") === document.getElementById('email_field').value &&
            this.getCookie("password") === document.getElementById('password_field').value) {

            window.open('poll.html', "_self");
        } else {
            alert("Incorrect login or password");
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