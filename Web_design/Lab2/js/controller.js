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
}