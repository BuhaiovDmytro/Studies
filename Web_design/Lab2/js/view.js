
export default class View {

    constructor(){
        this.poll_counter = 0;
    }

    view_profile(cur_user) {

        var xhr = new XMLHttpRequest();
        xhr.open('GET', "profile.html", true);
        xhr.onreadystatechange = function () {
            if (this.readyState !== 4) return;
            if (this.status !== 200) return;
            document.getElementById("tab_name").innerHTML = cur_user.name;
            document.getElementById("tab_email").innerHTML = cur_user.email;
            document.getElementById("tab_sex").innerHTML = cur_user.sex;
            document.getElementById("tab_birthday").innerHTML = cur_user.birthday;

            var sp1 = document.createElement(cur_user.birthday);

            document.replaceChild(document.getElementById("tab_birthday"), sp1);
        };

        xhr.send();
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
