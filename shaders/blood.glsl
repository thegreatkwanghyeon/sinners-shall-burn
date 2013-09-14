uniform sampler2D texture;
uniform vec2 center; //center 은 여기서 마우스 포인트 좌표를 의미한다
void main()
{
	float distanceCenter = (1.0-(1.2*distance(gl_TexCoord[0].xy,center)));
    gl_FragColor= vec4(sqrt(distanceCenter),sqrt(pow(distanceCenter,2)-0.25),sqrt(pow(distanceCenter,2)-0.25),1.0) * texture2D(texture,gl_TexCoord[0].xy);

    // float distance (vec2 _p1, vec2 _p2)
    // 두 점의 거리를 반환

    // vec4 texture2D(sampler2D _texture, vec2 _position);
    // texture fragment 의 색상값 (r,g,b,a) 를 반환함
}
 