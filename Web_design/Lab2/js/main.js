import View from "./view.js";
import Controller from "./controller.js"

let new_view = new View();
let ctrl = new Controller();

const poll_btn = document.getElementById('poll_btn');
const about_btn = document.getElementById('about_btn');
const signout_btn = document.getElementById('signout_btn');
const profile_btn = document.getElementById('profile_btn');
const signup_btn = document.getElementById('signupbutton');
const signin_btn = document.getElementById('signinbutton');
const publish_btn = document.getElementById('publish_btn');
const profie_load = document.getElementById('profile_body');

let vote_btns = [];

if(poll_btn) {
    poll_btn.addEventListener('click', {
        handleEvent: function (event) {
            new_view.poll();
        }
    });
}

if(about_btn) {
    about_btn.addEventListener('click', {
        handleEvent: function (event) {
            new_view.about();
        }
    });
}

if(signout_btn) {
    signout_btn.addEventListener('click', {
        handleEvent: function (event) {
            new_view.signout();
        }
    });
}

if(profile_btn) {
    profile_btn.addEventListener('click', {
        handleEvent: function (event) {
            new_view.profile();
        }
    });
}

if(signup_btn) {
    signup_btn.addEventListener('click', {
        handleEvent: function (event) {
            ctrl.signup();
        }
    });
}

if(signin_btn) {
    signin_btn.addEventListener('click', {
        handleEvent: function (event) {
            ctrl.signin_onclick();
        }
    });
}

if(publish_btn) {
    publish_btn.addEventListener('click', {
        handleEvent: function (event) {

            let poll_id = new_view.publish();
            let vote_btn = document.getElementById(poll_id + '_btn');

                vote_btn.addEventListener('click', {
                    handleEvent: function (event) {

                        new_view.vote(poll_id, ctrl.get_vote());
                    }
                });
                vote_btns.push(vote_btn);
        }
    });
}

if(profie_load) {
    profie_load.addEventListener('mousemove', {
        handleEvent: function (event) {

            new_view.view_profile(ctrl.get_user());
        }
    });
}

