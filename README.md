<div class="welcome">
  <h1>Hi there, welcome to Codyshell 👋</h1>
  <subtitle>Codyshell (also know as Minishell in the 42 curriculum) is a mini version of the shell bash.
  Codyshell was made by vdkJelle and TessavdL.</subtitle>
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
    <li>Copy the url of the repository</li>
    <li>Open up a terminal</li>
    <li>Clone the repostiory with the following command:
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
    <li>Press enter and you're done!</li>
  </ol>
</div>
<div class="run">
  <h2>How to run codyshell</h2>
  <ol>
    <li>Change your directory to the newly created directory
      <p>
        ```
        cd name_of_target_directory
        ```
      </p>
    </li>
    <li>Use the makefile to build the project. Type in `make` into the terminal and press enter. The makefile will build the project and create an executable called codyshell</li>
    <li>Now you can run codyshell by typing in `./codyshell`</li>
    <li>The makefile also allows you to rebuild the project with: `make re`, remove all object files with `make clean` and remove all object files and the executable with `make fclean`</li>
  </ol>
</div>
<div class="commands">
  <h2>What can codyshell do?</h2>
  <ul>
    <li>Codyshell runs single commands, multiple commands seperated with a semicolom `;` and commands with pipes in between them</li>
    <li>Codyshell handles environmental variables with `$variable_name` which will expand to the value of the variable name if it exists.
    <li>Codyshell can also handle `$0`, which displays the exit status of the previosly executed command.
    <li>Codyshell handles redirections `<`, `<<`(heredoc), `>` and `>>`</li>
    <li>Codyshell handles escape characters</li>
    <li>Codyshell responds to the following signals: ctrl + c, ctrl + d and ctrl + /</li>
    <li>Codyshell does not handle multiline commands, nor the following control operators ||, &&, &, ;;, ;&, ;;&, |&, (, and ).
  </ul>
</div>

