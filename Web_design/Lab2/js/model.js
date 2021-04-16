import Controller from "./controller.js";

export default class User {
    constructor(name, email, sex, birthday, password) {
        this.name = name;
        this.email = email;
        this.sex = sex;
        this.birthday = birthday;
        this.password = password;
    }

    add_user(){
        let ctrl = new Controller();
        ctrl.setCookie("name_", '', 30);
        ctrl.setCookie("email_", '', 30);
        ctrl.setCookie("sex", '', 30);
        ctrl.setCookie("birthday", '', 30);
        ctrl.setCookie("password", '', 30);

        ctrl.setCookie("name_", this.name, 30);
        ctrl.setCookie("email_", this.email, 30);
        ctrl.setCookie("sex", this.sex, 30);
        ctrl.setCookie("birthday", this.birthday, 30);
        ctrl.setCookie("password", this.password, 30);
    }
}