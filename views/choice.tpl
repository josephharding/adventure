<div class="choice">{{data['choicetext']}}</div>

<ol>
%for index, option in enumerate(data['options']):
  <li class="option"><a href="/{{data['choice']}}/{{index}}">{{option}}</a></li>
%end
</ol>
