import Controller from "./controller.js";

export default class View {

    constructor(){
        this.poll_counter = 0;
    }

    view_profile(cur_user) {

        var value = document.createElement('TD');
        value.id = "tab_name";
        var value_content = document.createTextNode(cur_user.name);
        value.appendChild(value_content);
        var place = document.getElementById("tab_name");
        var parentDiv = place.parentNode;
        parentDiv.replaceChild(value, place);

        var value_email = document.createElement('TD');
        value_email.id = "tab_email";
        var value_content_email = document.createTextNode(cur_user.email);
        value_email.appendChild(value_content_email);
        var place_email = document.getElementById("tab_email");
        var parentDiv_email = place_email.parentNode;
        parentDiv_email.replaceChild(value_email, place_email);

        var value_sex = document.createElement('TD');
        value_sex.id = "tab_sex";
        var value_content_sex = document.createTextNode(cur_user.sex);
        value_sex.appendChild(value_content_sex);
        var place_sex = document.getElementById("tab_sex");
        var parentDiv_sex = place_sex.parentNode;
        parentDiv_sex.replaceChild(value_sex, place_sex);

        var value_birthday = document.createElement('TD');
        value_birthday.id = "tab_birthday";
        var value_content_birthday = document.createTextNode(cur_user.birthday);
        value_birthday.appendChild(value_content_birthday);
        var place_birthday = document.getElementById("tab_birthday");
        var parentDiv_birthday = place_birthday.parentNode;
        parentDiv_birthday.replaceChild(value_birthday, place_birthday);

    }

    publish() {

        var question_str = document.getElementById('question_inp').value;
        var ans1_str = document.getElementById('ans1_inp').value;
        var ans2_str = document.getElementById('ans2_inp').value;

        var poll_id = 'poll' + this.poll_counter;
        this.poll_counter++;

        var html_polla ='    <div id = "' + poll_id + '">\n' +
            '<label class="mdc-top-app-bar__title">' + question_str + '</label>\n' +
            '\n' +
            '<div class="mdc-form-field">\n' +
            '    <div class="mdc-radio">\n' +
            '        <input class="mdc-radio__native-control" type="radio" id="' + ans1_str + '" name="radios" checked>\n' +
            '        <div class="mdc-radio__background">\n' +
            '            <div class="mdc-radio__outer-circle"></div>\n' +
            '            <div class="mdc-radio__inner-circle"></div>\n' +
            '        </div>\n' +
            '        <div class="mdc-radio__ripple"></div>\n' +
            '    </div>\n' +
            '    <label for="' + ans1_str + '">' + ans1_str + '</label>\n' +
            '\n' +
            '    <div class="mdc-radio">\n' +
            '        <input class="mdc-radio__native-control" type="radio" id="' + ans2_str + '" name="radios" checked>\n' +
            '        <div class="mdc-radio__background">\n' +
            '            <div class="mdc-radio__outer-circle"></div>\n' +
            '            <div class="mdc-radio__inner-circle"></div>\n' +
            '        </div>\n' +
            '        <div class="mdc-radio__ripple"></div>\n' +
            '    </div>\n' +
            '    <label for="' + ans2_str + '">' + ans2_str + '</label>\n' +
            '</div>\n' +
            '        <button class="mdc-button foo-button" id = "' + poll_id + '_btn' + '">\n' +
            '            <div class="mdc-button__ripple"></div>\n' +
            '            <span class="mdc-button__label">Vote</span>\n' +
            '        </button>\n' +
            '\n' +
            '        </div>';

        var menu = document.createElement('div');
        menu.id = 'menu';
        menu.innerHTML = html_polla;
        document.body.appendChild(menu);

        return poll_id;
    }

    vote(poll_id, vote) {

        if (vote !== '') {

            document.getElementById(poll_id).innerHTML =
                '<label class="mdc-top-app-bar__title">You voted "' + vote + '"</label>';
        }
    }

    about() {

        window.open('about.html', "_self");
    }

   poll() {
        window.open('poll.html', "_self");
    }

    profile() {

        window.open('profile.html', "_self");
    }

    signout() {

        window.open('signin.html', "_self");
    }

}
