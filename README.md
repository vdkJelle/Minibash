<!DOCTYPE html>
<html><div class="welcome">
  <h1>Hi there, welcome to codyshell 👋</h1>
  <subtitle>Codyshell (also know as Minishell in the 42 curriculum) is a mini version of the shell: bash.
  Codyshell is written in the C programming language and created by vdkJelle and TessavdL.</subtitle>
</div>
<div class="shell">
  <h2>What is a shell?</h2>
  <img src="https://i0.wp.com/matt.might.net/articles/bash-by-example/images/bash-shell.png" />
  <p>A shell is a program that runs in a terminal. A terminal is simply a program that opens up a window in which you can interact with the shell. A shell
    takes in commands from a user and gives them to an operating system, which execute the commands. The results are then displayed in the terminal. Codyshell is based on the shell bash.</p>
</div>
<div class="clone">
  <h2>How to clone the repository</h2>
  <ol>
    <li>Above the list of files, click <code>< > Code</code>.</li>
    <li>Copy the url of the repository.</li>
    <li>Open up a terminal.</li>
    <li>Clone the repostiory using the <code>git clone</code> command. You can type in <code>git clone</code> and paste the url you just copied after it. It is also recommended to specify the target location (e.g. where you would like the repository to be cloned to).
<p>

```
git clone <url> <target_location>
```
  </p>
      <p>For example:</p><p>

```
git clone https://github.com/Minibash codyshell
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
    <li>Change your directory to the directory you've just cloned.</li><p>

```
cd <target_location>
```
  </p>
    <li>Use the makefile to build the project. Type in <code>make</code> into the terminal and press enter. The makefile will build the project and create an executable called codyshell.</li>
    <li>The makefile also allows you to rebuild the project with: <code>make re</code>, remove all object files with <code>make clean</code> and remove all object files and the executable with <code>make fclean</code>.</li>
    <li>Now you can run codyshell by typing in <code>./codyshell</code>.</li>
    <li>If you wish to exit codyshell you can use the <code>exit</code> command, press <code>ctrl + c</code> or close the terminal.</li>
  </ol>
</div>
<div class="commands">
  <h2>What can codyshell do?</h2>
  <p>To use codyshell you can type in commands and press enter. Codyshell can execute several builtin commands: cd, echo, exit, export and pwd. All other commands by executed by using execve.</p>
  <ul>
    <li>
      <p>Commands are seperated form each other by control operators. Codyshell runs single commands, multiple commands (separated by <code>;</code>) and commands with pipes <code>|</code> in between them.<br>
      The <code>;</code> operator simply separates commands from each other. The <code>|</code> operator (also called a pipe) also allows the user to use the output of the previous command as input of the next command.<br>
      Codyshell does not handle the following control operators: <code>||</code>, <code>&&</code>, <code>&</code>, <code>;;</code>, <code>;&</code>, <code>;;&</code>, <code>|&&</code>, <code>(</code> and <code>)</code>.</p>
    </li>
    <li>
      <p>Commands can consists of one or more words. The first word is always the name of the command that is to be executed. The rest of the words are arguments that can change the behavior of the command that is executed.<br>Words are seperated by metacharacters. Codyshell handles <code>spaces</code>, <code>tabs</code>, <code>'<'</code>, <code>'>'</code>, <code>;</code> and <code>|</code>.<br>
      Codyshell does not handle the following metacharacters: <code>&</code>, <code>(</code>, and <code>)</code>.</p>
    <li>Codyshell handles environmental variables with <code>$var</code> which will expand to the value of the variable name if it exists.</li>
    <li>Codyshell can also handle <code>$0</code>, which displays the exit status of the previosly executed command.</li>
    <li>Codyshell handles redirections <code><</code>, <code><<</code>(heredoc), <code>></code> and <code>>></code>.</li>
    <li>Codyshell handles escape characters.</li>
    <li>Codyshell responds to the following signals: <code>ctrl + c</code>, <code>ctrl + d</code> and <code>ctrl + /</code>.</li>
    <li>Codyshell does not handle multiline commands.</li>
  </ul>
</div>
<div class="learning_objectives">
  <h2>What did we learn?</h2>
  <p>This is the first time we built a shell from scratch. We learned how to change the input from the user (the commands) into something that can be executed by the operating system. We had to learn how to write a lexer and a parser. We had to make sure that the input was valid and return the correct error messages in case of invalid input. The project also required us to use and manage file descriptors extensively. For redirections, but also for pipes, which was the trickiest part of the project. Lastly we also learned about processes and signals.</p>
</div>
<div class="doggo">
  <h2>Why is the shell called codyshell?</h2>
  <p>Because Cody is best boi</p>
</div>
</html>

  ![image](https://github.com/vdkJelle/Minibash/assets/72658914/875429dc-4a3f-4148-a6fe-276b988df73b)

