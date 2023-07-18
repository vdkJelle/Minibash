<div class="welcome">
  <h1>Hi there, welcome to Codyshell 👋</h1>
  <subtitle>Codyshell (also know as Minishell in the 42 curriculum) is a mini version of the shell: bash.
  Codyshell is written in the C programming language and created by vdkJelle and TessavdL.</subtitle>
</div>
<div class="shell">
  <h2>What is a shell?</h2>
  <img src="https://i0.wp.com/matt.might.net/articles/bash-by-example/images/bash-shell.png" />
  <p>A shell is a program that runs in a terminal. A terminal is simply a program that opens up a window in which you can interact with the shell. A shell
    takes in commands from a user and gives them to an operating system to execute. The results are then displayed in the terminal. Codyshell is based on the shell bash.</p>
</div>
<div class="clone">
  <h2>How to clone the repository</h2>
  <ol>
    <li>Above the list of files, click < > Code.</li>
    <li>Copy the url of the repository.</li>
    <li>Open up a terminal.</li>
    <li>Clone the repostiory using the `git clone` command. You can type in `git clone ` and paste the url you just copied after it. It is also recommended to specify the target location (e.g. where you would like the repository to be cloned to).
      <p>
        ```
        git clone url_you_just_copied name_of_target_directory
        ```
      </p>
      <p>For example:</p>
      <p>
      ```
      git clone https://github.com/vdkJelle/Minibash codyshell
      ```
      </p>
      <p>This will create a new directory called codyshell and will clone the github repostiory into it. Please note if you do not specify name_of_target_directory, the repostitory will be cloned into your working directory.</p>
    </li>
    <li>Press enter and you've successfully cloned the repostitory!</li>
  </ol>
</div>
<div class="run">
  <h2>How to run codyshell</h2>
  <ol>
    <li>Change your directory to the newly created directory.
      <p>
        ```
        cd name_of_target_directory
        ```
      </p>
    </li>
    <li>Use the makefile to build the project. Type in `make` into the terminal and press enter. The makefile will build the project and create an executable called codyshell.</li>
    <li>The makefile also allows you to rebuild the project with: `make re`, remove all object files with `make clean` and remove all object files and the executable with `make fclean`.</li>
    <li>Now you can run codyshell by typing in `./codyshell`.</li>
    <li>If you wish to exit codyshell you can type in `exit`, press ctrl + c or close the terminal.</li>
  </ol>
</div>
<div class="commands">
  <h2>What can codyshell do?</h2>
  <p>To use cody shell you can type in commands and press enter. Codyshell can execute several builtin commands: cd, echo, exit, export and pwd. All other commands by executed by using execve.</p>
  <ul>
    <li>Codyshell runs single commands, multiple commands seperated with a semicolom `;` and commands with pipes in between them.</li>
    <li>Codyshell handles environmental variables with `$variable_name` which will expand to the value of the variable name if it exists.</li>
    <li>Codyshell can also handle `$0`, which displays the exit status of the previosly executed command.</li>
    <li>Codyshell handles redirections `<`, `<<`(heredoc), `>` and `>>`.</li>
    <li>Codyshell handles escape characters.</li>
    <li>Codyshell responds to the following signals: ctrl + c, ctrl + d and ctrl + /.</li>
    <li>Codyshell does not handle multiline commands, nor the following control operators ||, &&, &, ;;, ;&, ;;&, |&, (, and ).</li>
  </ul>
</div>
<div class="learning_objectives">
  <h2>What did we learn?</h2>
  <p>This is the first time we build a shell from scratch. We learned how to change the input from the user (the commands) into something that can be executed by the operating system. We had to learn how to write a lexer and a parser. We had to make sure that the input was valid and return the correct error messages in case of invalid input. The project also required us to use and manage file descriptors extensively. For redirections, but also for pipes, which was the trickiest part of the project. Lastly we also learned about processes and signals.</p>
</div>
<div class="end">
  <h2>What did we learn?</h2>
  <p>This is the first time we build a shell from scratch. We learned how to change the input from the user (the commands) into something that can be executed by the operating system. We had to learn how to write a lexer and a parser. We had to make sure that the input was valid and return the correct error messages in case of invalid input. The project also required us to use and manage file descriptors extensively. For redirections, but also for pipes, which was the trickiest part of the project. Lastly we also learned about processes and signals.</p>
</div>
